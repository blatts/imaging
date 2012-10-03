// -*- mode: C++/lah -*-
// Time-stamp: "2012-10-03 15:30:26 sb"

/*
  file       image_window.cc
  copyright  (c) Sebastian Blatt 2010, 2011, 2012

 */

#include "gui_ids.hh"
#include "image_window.hh"

#include <wx/dcbuffer.h>
#include <algorithm>
#include <sstream>


/* Calculate 3 byte RGB value corresponding to interpolating floating
   point value T (assumed to be in [0,1]) between minimum and maximum
   of palette PAL of length N.
 */
void interpolate_color(float t, unsigned char* rgb, unsigned char* pal, size_t n){
  float x = t*(n-1);
  unsigned char z=0;
  size_t j = (size_t)floor(x);
  if(j>=n){j=n-1;}
  x -= j;
  j *= 3;
  z = pal[j];   rgb[0] = z + (unsigned char)((pal[j+3]-z) * x);
  z = pal[j+1]; rgb[1] = z + (unsigned char)((pal[j+4]-z) * x);
  z = pal[j+2]; rgb[2] = z + (unsigned char)((pal[j+5]-z) * x);
}

/*
  Rescale floating point value T to value in [0,1] by linear
  interpolation from interval [T0,T1]. Then calculate corresponding
  3 byte color code RGB from palette PAL of size N.
 */
void interpolate_color(float t, float t0, float t1,
                       unsigned char* rgb, unsigned char* pal, size_t n)
{
  if(t<t0)      {interpolate_color(0.0f,rgb,pal,n);}
  else if(t>t1) {interpolate_color(1.0f,rgb,pal,n);}
  else          {interpolate_color((t-t0)/(t1-t0),rgb,pal,n);}
}


Axes::Axes()
  : display_pad_w(10),
    display_pad_h(10),
    axes_padding(10),
    ticks_outside(true),
    major_ticks(5),
    minor_ticks(3),
    major_tick_length(4),
    minor_tick_length(2),
    axes_extent(wxRect(0,0,1,1))
{
}

Axes::~Axes(){
}

void Axes::Draw(wxDC& dc, size_t client_width, size_t client_height){
  std::ostringstream os;
  os.setf(std::ios::fixed);
  os.setf(std::ios::showpoint);
  size_t W = client_width, H = client_height;

  float dxmajor = (float)(W-2*display_pad_w-2*axes_padding)/(major_ticks-1);
  float dxminor = dxmajor/(minor_ticks+1);
  float dymajor = (float)(H-2*display_pad_h-2*axes_padding)/(major_ticks-1);
  float dyminor = dymajor/(minor_ticks+1);
  float xoffset = display_pad_w+axes_padding;
  float yoffset = display_pad_h+axes_padding;

  int mintl = minor_tick_length, majtl = major_tick_length;
  if(!ticks_outside){
    mintl *= -1;
    majtl *= -1;
  }

  for(size_t i=0; i<major_ticks; ++i){
    size_t x = (size_t)(xoffset+i*dxmajor);
    size_t y = (size_t)(yoffset+i*dymajor);
    size_t x0 = xoffset;
    size_t y0 = yoffset;
    dc.DrawLine(x,y0,x,y0-majtl);
    dc.DrawLine(x,H-y0,x,H-y0+majtl);
    dc.DrawLine(x0,y,x0-majtl,y);
    dc.DrawLine(W-x0,y,W-x0+majtl,y);

    os.precision(1);
    os << axes_extent.x + (int)(i * (float)axes_extent.width / (major_ticks-1));
    wxString nx = wxString::FromAscii(os.str().c_str()); os.str("");
    wxCoord nw, nh;
    dc.GetTextExtent(nx,&nw,&nh);
    dc.DrawText(nx,x-nw/2,y0-(ticks_outside?majtl:0)-nh);
    dc.DrawText(nx,x-nw/2,H-y0+(ticks_outside?majtl:0));

    os.precision(1);
    os << axes_extent.y + (int)(i * (float)axes_extent.height / (major_ticks-1));
    wxString ny = wxString::FromAscii(os.str().c_str()); os.str("");
    dc.GetTextExtent(ny,&nw,&nh);
    dc.DrawText(ny,x0-(ticks_outside?majtl:0)-nw,y-nh/2);
    dc.DrawText(ny,W-x0+(ticks_outside?majtl:0),y-nh/2);


    if(i<major_ticks-1){
      for(size_t j=0; j<minor_ticks; ++j){
        size_t xx = (size_t)(xoffset+i*dxmajor+(j+1)*dxminor);
        size_t yy = (size_t)(yoffset+i*dymajor+(j+1)*dyminor);
        dc.DrawLine(xx,y0,xx,y0-mintl);
        dc.DrawLine(xx,H-y0,xx,H-y0+mintl);
        dc.DrawLine(x0,yy,x0-mintl,yy);
        dc.DrawLine(W-x0,yy,W-x0+mintl,yy);
      }
    }
  }
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.DrawRectangle(xoffset,yoffset,
                   W-2*display_pad_w-2*axes_padding+1,
                   H-2*display_pad_h-2*axes_padding+1);
}


DEFINE_EVENT_TYPE(wxEVT_IMAGE_PANEL)

BEGIN_EVENT_TABLE(ImagePanel,wxPanel)
EVT_PAINT(ImagePanel::OnPaint)
EVT_ERASE_BACKGROUND(ImagePanel::OnEraseBackground)
EVT_LEFT_DOWN(ImagePanel::OnMouseLeftDown)
EVT_LEFT_UP(ImagePanel::OnMouseLeftUp)
EVT_MOTION(ImagePanel::OnMouseMove)
END_EVENT_TABLE()


ImagePanel::ImagePanel(wxFrame* parent,
                       wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size
                      )
: wxPanel(parent,id,pos,size),
  display_pad_w(45),
  display_pad_h(45),
  caret(0,0,0,0),
  caret_final(0,0,0,0),
  drawing_caret(false),
  caret_display(false),
  zoom_in(false),
  palette_display(true),
  info_palmin(0),
  info_palmax(0),
  info_palette(NULL),
  info_palette_size(0),
  axes_display(true),
  axes_offset(5),
  major_ticks(10),
  minor_ticks(5),
  major_tick_length(5),
  minor_tick_length(3),
  com_display(true),
  com(0,0),
  statistics_display(true),
  roi_stat(NULL),
  roi_labels(NULL),
  statistics_x0(20),
  statistics_y0(25)
{
  SetBackgroundColour(*wxBLACK); // will automatically draw bg on X, but not Win32
  SetBackgroundStyle(wxBG_STYLE_CUSTOM); // necessary for wxBufferedPaintDC

  SetDisplaySize(size.GetWidth(),size.GetHeight()); // sets display_width, display_height
  info_data_roi = wxRect(0,0,display_width,display_height),
  info_display_roi = wxRect(0,0,display_width,display_height),


  //wxLogMessage(wxT("Create ImagePanel(%d,%d)"),display_width,display_height);
  bmpdc.SelectObject(bmp);
}

ImagePanel::~ImagePanel(){
  FreeBitmap();
}

// After calling this during a resize event, info_display_roi becomes
// invalid! Needs to be updated by caller with SetDisplayROI !!!
void ImagePanel::SetDisplaySize(size_t display_width_, size_t display_height_){
  display_width = display_width_;
  display_height = display_height_;
  display_rect = wxRect(display_pad_w,display_pad_h,
                        display_width-2*display_pad_w,
                        display_height-2*display_pad_h);
  palette_bmp_w = display_width-10;
  palette_bmp_h = 10;
  if(info_palette){
    palette_bmp.Create(palette_bmp_w,palette_bmp_h);
    palette_mdc.SelectObject(palette_bmp);
    SetPaletteInfo(info_palette,info_palette_size);
  }
}

void ImagePanel::SetPaletteInfo(unsigned char* p, size_t size){
  if(!p || !size){
    return;
  }
  info_palette = p;
  info_palette_size = size;

  float dt = 1.0f/palette_bmp_w;
  unsigned char rgb[3] ={0,0,0};
  for(size_t i=0; i<palette_bmp_w; ++i){
    interpolate_color(i*dt,rgb,info_palette,info_palette_size);
    wxPen pen = wxPen(wxColour(rgb[0],rgb[1],rgb[2]));
    palette_mdc.SetPen(pen);
    palette_mdc.DrawLine(i,0,i,palette_bmp_h);
    palette_mdc.SetPen(*wxTRANSPARENT_PEN);
  }
}

void ImagePanel::draw_axes(wxDC& dc){
  wxPen p = wxPen(wxColour(*wxGREEN));
  dc.SetPen(p);
  std::ostringstream os;
  os.setf(std::ios::fixed);
  os.setf(std::ios::showpoint);

  float dxmajor = (float)(info_display_roi.width)/(major_ticks-1);
  float dxminor = dxmajor/(minor_ticks+1);
  float dymajor = (float)(info_display_roi.height)/(major_ticks-1);
  float dyminor = dymajor/(minor_ticks+1);
  float xoffset = (GetDisplayWidth()-info_display_roi.width)/2.0;
  float yoffset = (GetDisplayHeight()-info_display_roi.height)/2.0;
  for(size_t i=0; i<major_ticks; ++i){
    size_t x = display_pad_w+(size_t)(xoffset+i*dxmajor);
    size_t y = display_pad_h+(size_t)(yoffset+i*dymajor);
    size_t x0 = display_pad_w+(size_t)xoffset-axes_offset;
    size_t y0 = display_pad_h+(size_t)yoffset-axes_offset;
    dc.DrawLine(x,y0,x,y0-major_tick_length);
    dc.DrawLine(x,display_height-y0,x,display_height-y0+major_tick_length);
    dc.DrawLine(x0,y,x0-major_tick_length,y);
    dc.DrawLine(display_width-x0,y,display_width-x0+major_tick_length,y);

    os.precision(1);
    os << info_data_roi.x + (int)(i * (float)info_data_roi.width / (major_ticks-1));
    wxString nx = wxString::FromAscii(os.str().c_str()); os.str("");
    wxCoord nw, nh;
    dc.GetTextExtent(nx,&nw,&nh);
    //dc.DrawText(nx,x-nw/2,y0-major_tick_length-nh);
    dc.DrawText(nx,x-nw/2,display_height-y0+major_tick_length);

    os.precision(1);
    os << info_data_roi.y + (int)(i * (float)info_data_roi.height / (major_ticks-1));
    wxString ny = wxString::FromAscii(os.str().c_str()); os.str("");
    dc.GetTextExtent(ny,&nw,&nh);
    dc.DrawText(ny,x0-major_tick_length-nw,y-nh/2);
    //dc.DrawText(ny,display_width-x0+major_tick_length,y-nh/2);


    if(i<major_ticks-1){
      for(size_t j=0; j<minor_ticks; ++j){
        size_t xx = display_pad_w+(size_t)(xoffset+i*dxmajor+(j+1)*dxminor);
        size_t yy = display_pad_h+(size_t)(yoffset+i*dymajor+(j+1)*dyminor);
        dc.DrawLine(xx,y0,xx,y0-minor_tick_length);
        dc.DrawLine(xx,display_height-y0,xx,display_height-y0+minor_tick_length);
        dc.DrawLine(x0,yy,x0-minor_tick_length,yy);
        dc.DrawLine(display_width-x0,yy,display_width-x0+minor_tick_length,yy);
      }
    }
  }
}

void ImagePanel::draw_palette_info(wxDC& dc){
  std::ostringstream os;
  os.setf(std::ios::fixed);
  os.setf(std::ios::showpoint);

  wxSize s;
  for(size_t i=0; i<info_palette_size; ++i){
    int x = 5 + (int)(i * ((float)palette_bmp_w) / (info_palette_size-1));
    os.precision(1);
    os << info_palmin + (info_palmax-info_palmin)/(info_palette_size-1) * i;
    s = dc.GetTextExtent(wxString::FromAscii(os.str().c_str()));
    if(i>0){ x -= s.GetWidth()/2; }
    if(i==info_palette_size-1) { x -= s.GetWidth()/2; }
    dc.DrawText(wxString::FromAscii(os.str().c_str()),x,2);
    os.str("");
  }
  dc.Blit(5,2+s.GetHeight(),palette_bmp_w,palette_bmp_h,&palette_mdc,0,0);
}


void ImagePanel::draw_statistics_info(wxDC& dc){
  if(!roi_stat || !roi_labels){
    return;
  }
  std::ostringstream os;
  wxSize s;
  wxString o;
  size_t x0 = statistics_x0, y0 = statistics_y0;
  for(size_t i=0; i<roi_stat->size(); ++i){
    o = (*roi_labels)[i] + ": ";
    dc.DrawText(o,x0,y0);
    s = dc.GetTextExtent(o);
    x0 += s.GetWidth();

    os.precision(2);
    os << (*roi_stat)[i];
    o = wxString::FromAscii(os.str().c_str());
    os.str("");
    s = dc.GetTextExtent(o);
    dc.DrawText(o,x0,y0);
    x0 += s.GetWidth() + 10;
  }
}


void ImagePanel::OnPaint(wxPaintEvent&){
  wxBufferedPaintDC dc(this);
  wxCoord w,h;
  dc.GetSize(&w,&h);
  wxCoord bmpw, bmph;
  bmpdc.GetSize(&bmpw,&bmph);
  //wxLogMessage(wxT("ImagePanel::OnPaint dc size %d x %d, bmp size %d x %d"),w,h,bmpw,bmph);

  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxBLACK_BRUSH);
  dc.DrawRectangle(0,0,w,h);

  dc.Blit(display_rect.x,display_rect.y,
          //w,h,
          std::min(display_rect.width,w),
          std::min(display_rect.height,h),
          &bmpdc,0,0);

  wxFont fnt = wxFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL,false,wxT(""),
                      wxFONTENCODING_DEFAULT);
  dc.SetFont(fnt);
  dc.SetTextBackground(*wxBLACK);
  dc.SetTextForeground(*wxGREEN);

  if(axes_display){
    draw_axes(dc);
  }
  if(palette_display && info_palette){
    draw_palette_info(dc);
  }
  if(com_display){
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawCircle(com.x,com.y,5);
  }
  if(statistics_display){
    draw_statistics_info(dc);
  }
  if(caret_display){
    if(zoom_in){
      dc.SetPen(*wxGREEN_PEN);
    }
    else if(select_marker){
      dc.SetPen(*wxRED_PEN);
    }
    else{
      dc.SetPen(*wxTRANSPARENT_PEN);
    }
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(caret.x,caret.y,caret.width,caret.height);
  }
}


void ImagePanel::RecreateBitmap(const wxImage& new_image){
  FreeBitmap();
  bmp = wxBitmap(new_image);
  bmpdc.SelectObject(bmp);
  Refresh();
}

void ImagePanel::FreeBitmap(){
  bmpdc.SelectObject(wxNullBitmap);
}

void ImagePanel::OnMouseLeftDown(wxMouseEvent& evt){
  //wxLogMessage("OnLeftDown %d,%d",evt.GetX(),evt.GetY());
  caret.x = evt.GetX();
  caret.y = evt.GetY();
  drawing_caret = true;
  caret_display = true;
  if(evt.ControlDown()){
    zoom_in = false;
    select_marker = true;
  }
  else {
    zoom_in = true;
    select_marker = false;
  }
}

void ImagePanel::OnMouseLeftUp(wxMouseEvent& evt){
  wxCoord x = evt.GetX(), y = evt.GetY();
  //wxLogMessage("OnLeftDown %d,%d",x,y);
  if(drawing_caret){
    caret.width = x - caret.x;
    caret.height = y - caret.y;

    // Normalize caret
    caret_final = caret;
    if(caret_final.width < 0){
      caret_final.x += caret_final.width;
      caret_final.width = -caret_final.width;
    }
    if(caret_final.height < 0){
      caret_final.y += caret_final.height;
      caret_final.height = -caret_final.height;
    }

    // Limit caret to bitmap display area
    caret_final.Intersect(wxRect(display_pad_w,display_pad_h,
                                 display_width-2*display_pad_w,
                                 display_height-2*display_pad_h));

    // Translate caret into bitmap coordinates
    caret_final.x -= display_pad_w;
    caret_final.y -= display_pad_h;

    //wxLogMessage(wxT("Caret done  : %d %d %d %d"),caret.x,caret.y,caret.width,caret.height);
    //wxLogMessage(wxT("Caret final : %d %d %d %d"),caret_final.x,caret_final.y,caret_final.width,caret_final.height);
    zoom_in = !evt.ShiftDown();
    wxCommandEvent evt = wxCommandEvent(wxEVT_IMAGE_PANEL,ID_IMAGE_WINDOW_CARET_DONE);
    wxPostEvent(this,evt);
    Refresh();
    drawing_caret = false;
  }
}

void ImagePanel::OnMouseMove(wxMouseEvent& evt){
  if(drawing_caret && evt.LeftIsDown()){
    wxCoord x = evt.GetX(), y = evt.GetY();
    caret.width = x - caret.x;
    caret.height = y - caret.y;
    Refresh();
  }
  else{
    drawing_caret = false;
  }
}


BEGIN_EVENT_TABLE(DataPanel,wxPanel)
EVT_PAINT(DataPanel::OnPaint)
END_EVENT_TABLE()

DataPanel::DataPanel(wxFrame* parent,
                     wxWindowID id,
                     const wxPoint& pos,
                     const wxSize& size
                    )
: wxPanel(parent,id,pos,size),
  padding_w(10),
  padding_h(10)
{
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

DataPanel::~DataPanel(){
}

void DataPanel::OnPaint(wxPaintEvent&){
  wxBufferedPaintDC dc(this);
  int w,h;
  GetClientSize(&w,&h);

  dc.SetBrush(*wxBLACK_BRUSH);
  dc.SetPen(*wxTRANSPARENT_PEN);
  dc.DrawRectangle(0,0,w,h);

  dc.SetPen(*wxGREEN_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxFont fnt = wxFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_NORMAL,false,wxT(""),
                      wxFONTENCODING_DEFAULT);
  dc.SetFont(fnt);
  dc.SetTextBackground(*wxBLACK);
  dc.SetTextForeground(*wxGREEN);
  Axes ax;
  ax.Draw(dc,w,h);
}





BEGIN_EVENT_TABLE(ImageFrame,wxFrame)
EVT_COMMAND(ID_IMAGE_WINDOW_CARET_DONE,wxEVT_IMAGE_PANEL,ImageFrame::OnCaretDone)
EVT_SIZE(ImageFrame::OnResize)
END_EVENT_TABLE()


// Free internal palette representation.
void ImageFrame::free_palette(){
  if(palette){
    delete[] palette;
    palette =NULL;
    palette_size= 0;
  }
}

// Reallocate internal palette representation.
void ImageFrame::create_palette(){
  free_palette();
  palette_size = 6;
  palette = new unsigned char[3*palette_size];
  std::fill(palette,palette+3*palette_size,0);
  palette[3*0 + 2] = 0x88; // dark blue
  palette[3*1 + 1] = 0x88; // dark cyan
  palette[3*1 + 2] = 0x88;
  palette[3*2 + 1] = 0x88; // dark green
  palette[3*3 + 0] = 0xdd; // yellow
  palette[3*3 + 1] = 0xdd;
  palette[3*4 + 0] = 0xcc; // red
  palette[3*5 + 0] = 0xff; // white
  palette[3*5 + 1] = 0xff;
  palette[3*5 + 2] = 0xff;
}

// Interpolate floating point data T between T0 and T1 into RGB image
// using palette PAL of size NPAL. Limit the updated region of RGB to
// region PALROI.
void ImageFrame::interpolate_image(float* t, float t0, float t1, unsigned char* rgb,
                                   unsigned char* pal, size_t npal, const wxRect& palroi)
{
  std::fill(rgb,rgb+3*width*height,0);
  size_t idx = 0;
  for(int j=0; j<palroi.height; ++j){
    for(int i=0; i<palroi.width; ++i){
      idx = (palroi.y + j)*width + (palroi.x+i);
      interpolate_color(t[idx],t0,t1,&(rgb[3*idx]),pal,npal);
    }
  }
}

bool ImageFrame::process_raw_data(){
  wxMutexLocker lock(*raw_image_data_mutex);
  if(!raw_image_data){
    wxLogError(wxT("ImageFrame::process_raw_data raw_image_data = NULL"));
    return false;
  }

  size_t area = width*height;

  // For displaying a regular image, just copy the data over
  if(!kinetics){
    //std::copy(*raw_image_data, (*raw_image_data)+area, processed_data);
    std::transform(*raw_image_data, (*raw_image_data)+area,
                   processed_data, StaticCaster<long, float>());
  }
  // For kinetics mode, need to calculate optical density. Put
  // calculated OD image into _beginning_ of processed_data.
  else{
    size_t subarea = width*(height/n_kinetics);
    std::fill(processed_data,processed_data+area,0);
    int idx_dark = 0, idx_shadow = 0, idx_light = 0;
    if(n_kinetics == 3){
      idx_dark = 0;
      idx_shadow = 1;
      idx_light = 2;
    }
    else if(n_kinetics == 2){
      idx_dark = 0; // no dark picture
      idx_shadow = 0;
      idx_light = 1;
    }
    else{ // only shadow picture
      idx_dark = 0;
      idx_shadow = 0;
      idx_light = 0;
    }
    long* idark = (*raw_image_data) + idx_dark * subarea;
    long* ishadow = (*raw_image_data) + idx_shadow * subarea;
    long* ilight = (*raw_image_data) + idx_light * subarea;

    float* od = processed_data;
    float a=0, b=0;

    if(n_kinetics == 3){
      for(size_t i=0; i<subarea; ++i){
        a = std::max(logf(std::max((float)(ilight[i]-idark[i]),0.0f)),-1.0f);
        b = std::max(logf(std::max((float)(ishadow[i]-idark[i]),0.0f)),-1.0f);
        od[i] = a-b;
      }
    }
    else if(n_kinetics == 2){
      for(size_t i=0; i<subarea; ++i){
        a = std::max(logf(std::max((float)(ilight[i]),0.0f)),-1.0f);
        b = std::max(logf(std::max((float)(ishadow[i]),0.0f)),-1.0f);
        od[i] = a-b;
      }
    }
    else{
      for(size_t i=0; i<subarea; ++i){
        a = std::max(logf(std::max((float)(ishadow[i]),0.0f)),-1.0f);
        od[i] = a;
      }
    }
  }
  return true;
}


void ImageFrame::roi_statistics(const wxRect& roi, std::vector<float>& roi_stat){
  size_t i=0, j=0, w=roi.width, h=roi.height;
  float t=0,tmin=0, tmax=0;
  float m1=0, cmx=0, cmy=0;
  float* od = processed_data;

  tmin = tmax = od[0];
  for(j=0; j<h; ++j){
    for(i=0; i<w; ++i){
      t = od[(roi.y+j)*width + (roi.x+i)];
      if(t<tmin){ tmin = t; }
      if(t>tmax){ tmax = t; }
      m1 += t;
      cmx += i*t;
      cmy += j*t;
    }
  }
  roi_stat.resize(8);
  roi_stat[0] = tmin; // minimum
  roi_stat[1] = tmax; // maximum
  roi_stat[2] = m1; // integrated
  roi_stat[3] = width*height>0 ? m1/(width*height) : 0; // mean
  roi_stat[4] = 0.0;
  //roi_stat[4] = width*height>1 ? sqrt(m2/(width*height-1)) : 0; // variance
  roi_stat[5] = 0;
  roi_stat[6] = cmx / m1; // center of mass x
  roi_stat[7] = cmy / m1; // center of mass y
}

/*
  Convert data frame coordinates P into display frame coordinates
  corresponding to ROI.
 */
wxPoint ImageFrame::data_frame_to_display_frame(const wxPoint& p){
  float x=p.x, y=p.y;

  // translate into roi frame
  x -= roi.x;
  y -= roi.y;
  //std::swap(x,y);

  // scale into uncentered display frame
  float sc = std::min(display_frame_scale_x,display_frame_scale_y);
  x *= sc;
  y *= sc;
  // translate into centered display frame
  x += display_frame_tr_x;
  y += display_frame_tr_y;

  return wxPoint((int)floor(x+.5),(int)floor(y+.5));
}

/*
  Convert display frame coordinates P with respect to ROI into data
  frame coordinates.
 */
wxPoint ImageFrame::display_frame_to_data_frame(const wxPoint& p){
  float x=p.x, y=p.y;

  // translate into uncentered display frame
  x -= display_frame_tr_x;
  y -= display_frame_tr_y;
  // scale into roi frame
  float sc = std::min(display_frame_scale_x,display_frame_scale_y);
  x /= sc;
  y /= sc;
  // translate into data frame
  //std::swap(x,y);
  x += roi.x;
  y += roi.y;

  return wxPoint((int)floor(x+.5),(int)floor(y+.5));
}



ImageFrame::ImageFrame(wxFrame* parent, const wxString& title,
                       const wxPoint& pos, const wxSize& size,
                       long** raw_image_data_,
                       wxMutex* raw_image_data_mutex_,
                       unsigned int width_, unsigned int height_
                      )
: wxFrame(parent,-1,title,pos,size),
  img_panel(NULL),
  data_panels(0),
  raw_image_data(raw_image_data_),
  raw_image_data_mutex(raw_image_data_mutex_),
  width(width_),
  height(height_),
  processed_data(NULL),
  processed_image(width,height),
  disp_image(width,height),
  palette(NULL),
  palette_size(0),
  palette_min(0),
  palette_max(0),
  palette_min_manual(0),
  palette_max_manual(0),
  palette_scale_manual(false),
  roi(0,0,width,height),
  roi_stat(8,0.0f),
  roi_labels(8,""),
  display_frame_scale_x(1.0f),
  display_frame_scale_y(1.0f),
  display_frame_tr_x(0),
  display_frame_tr_y(0),
  kinetics(false),
  n_kinetics(3)
{
  SetBackgroundColour(*wxBLACK);
  //wxLogMessage(wxT("Create ImageFrame(%d,%d)"),width,height);
  img_panel = new ImagePanel(this,wxNewId(),wxDefaultPosition,
                             wxSize(data_panels.size() == 0 ? width : (size_t)(3.0/4.0*width),
                                    height));

  for(size_t i=0; i<data_panels.size(); ++i){
    data_panels[i] = new DataPanel(this,wxNewId(),wxDefaultPosition,wxDefaultSize);
  }


  processed_data = new float[width*height];
  std::fill(processed_data,processed_data+width*height,0);

  create_palette();
  img_panel->SetPaletteInfo(palette,palette_size);
  const char* lbl[] = {"min","max","tot","mean","varx","vary","cmx","cmy"};
  for(size_t i=0; i<roi_labels.size(); ++i){
    roi_labels[i] = lbl[i];
  }
  img_panel->SetROIStatistics(&roi_stat,&roi_labels);
}

ImageFrame::~ImageFrame(){
  if(processed_data){
    delete[] processed_data;
    processed_data = NULL;
  }
  free_palette();
}

/*
  This is the meat. When raw_image_data has been updated from the main
  program, this function is called to update the display.

 */
void ImageFrame::UpdateData(){

  // (A) Convert the raw bytes into floating point representation,
  //     using OD formula if required.

  if(!process_raw_data()){
    return;
  }


  // (B) The Region Of Interest (ROI) might have changed. Update the
  //     internal rectangle representing the ROI and calculate
  //     statistics of the floating point data.

  wxRect total_image(0,0,width,height);
  if(kinetics){
    //total_image = wxRect(0,height/n_kinetics,width,height/n_kinetics);
    total_image = wxRect(0,0,width,height/n_kinetics);
  }
  wxRect palroi = total_image;
  palroi = palroi.Intersect(roi);
  //wxLogMessage(wxT("totalimg : %d %d %d %d"),total_image.x,total_image.y,
  //             total_image.width,total_image.height);
  //wxLogMessage(wxT("palroi : %d %d %d %d"),palroi.x,palroi.y,palroi.width,palroi.height);

  //std::vector<float> roi_tot;
  //roi_statistics(total_image,roi_tot);
  roi_statistics(palroi,roi_stat);
  //wxLogMessage(wxT("Total image [min,max] = [%f, %f]"),roi_tot[0],roi_tot[1]);
  //wxLogMessage(wxT("ROI [min,max] = [%f, %f]"),roi_stat[0],roi_stat[1]);


  // (C) Update the palette information and update the internal RGB
  //     image from the floating point data. Limit the color
  //     interpolation to ROI to increase speed.

  if(palette_scale_manual){
    palette_min = palette_min_manual;
    palette_max = palette_max_manual;
  }
  else if(palette_scale_next_image){
    palette_min = roi_stat[0]; // ROI min
    palette_max = roi_stat[1]; // ROI max
    palette_scale_next_image = false;
  }
  img_panel->SetPaletteInfoScale(palette_min,palette_max);
  //wxLogMessage(wxT("pal : %f, %f"),palette_min,palette_max);
  //wxLogMessage(wxT("roi_stat: %f %f %f %f %f %f %f %f"),roi_stat[0],
  //             roi_stat[1],roi_stat[2],roi_stat[3],roi_stat[4],
  //             roi_stat[5],roi_stat[6],roi_stat[7]);


  interpolate_image(processed_data,palette_min,palette_max,
                    processed_image.GetData(),palette,palette_size,palroi);

  roi = palroi;
  UpdateDisplay();
}

void ImageFrame::UpdateDisplay(){
  if(!img_panel){
    return;
  }

  // (D) Cut out the ROI from the RGB image, rotate it, rescale it.

  disp_image = processed_image.GetSubImage(roi);

  // update roi -> display scaling factors
  unsigned int W = img_panel->GetDisplayWidth();
  unsigned int H = img_panel->GetDisplayHeight();
  display_frame_scale_x = ((float)W) / roi.width;
  display_frame_scale_y = ((float)H) / roi.height;
  float scale = std::min(display_frame_scale_x,display_frame_scale_y);
  unsigned int w = std::min((unsigned int)(scale * roi.width),W);
  unsigned int h = std::min((unsigned int)(scale * roi.height),H);

  // rotate by swapping W,H, display_frame_scale_x,y, w,h
  //std::swap(W,H);
  //std::swap(display_frame_scale_x,display_frame_scale_y);
  //std::swap(w,h);

  // update roi -> display translation
  if(display_frame_scale_x < display_frame_scale_y){
    display_frame_tr_x = 0;
    display_frame_tr_y = (H - h) / 2;
  }
  else{
    display_frame_tr_x = (W - w) / 2;
    display_frame_tr_y = 0;
  }
  wxRect rroi = roi;
  //std::swap(rroi.x,rroi.y);
  //std::swap(rroi.width,rroi.height);
  img_panel->SetDataROI(rroi);
  img_panel->SetDisplayROI(wxRect(display_frame_tr_x,display_frame_tr_y,w,h));

  // Rotate image
  disp_image = disp_image.Rotate90();

  // Scale image
  disp_image.Rescale(w,h);//,wxIMAGE_QUALITY_HIGH);

  // Resize image memory to (W,H) and place original at
  // (display_frame_tr_x,display_frame_tr_y)
  disp_image.Resize(wxSize(W,H),wxPoint(display_frame_tr_x,display_frame_tr_y));


  // (E) Update display markers with new statistical data
  UpdateMarkers(roi,roi_stat);

  // (F) Finally update display panel with the ROI RGB image.

  img_panel->RecreateBitmap(disp_image);
}



/*
  Update statistical markers in ImagePanel. Convert data frame into
  display frame.
 */
void ImageFrame::UpdateMarkers(const wxRect& roi, const std::vector<float>& stat){
  wxPoint p_data((int)(roi.x + floor(stat[6]+.5)),(int)(roi.y + floor(stat[7]+.5)));
  wxPoint p_disp = data_frame_to_display_frame(p_data);
  img_panel->SetCOMMarker(p_disp);
}

/*
  Handle caret selection in ImagePanel here. Convert display frame
  coordinates back into data frame and choose new ROI correspondingly.
 */
void ImageFrame::OnCaretDone(wxCommandEvent&){
  wxRect r = img_panel->GetCaret();
  if(img_panel->ZoomingIn()){
    if(r.width == 0 || r.height == 0){
      return;
    }

    wxPoint p1(r.x,r.y);
    wxPoint p2(r.x+r.width,r.y+r.height);
    wxPoint q1 = display_frame_to_data_frame(p1);
    wxPoint q2 = display_frame_to_data_frame(p2);

    if(q1.x > q2.x){ std::swap(q1.x,q2.x); }
    if(q1.y > q2.y){ std::swap(q1.y,q2.y); }

    wxRect r = wxRect(q1,q2);

    // Constrain r to full image
    if(r.x < 0) {r.width += r.x; r.x = 0;}
    if(r.y < 0) {r.height += r.y; r.y = 0;}
    if(r.width > (int)width){r.width = width;}
    if(r.height > (int)height){r.height = height;}
    if(r.width < 0){r.width = 0;}
    if(r.height < 0){r.height = 0;}

    // Check whether new ROI is empty
    if(r.IsEmpty()){
      wxLogMessage(wxT("Invalid ROI: %d %d %d %d"),r.x,r.y,r.width,r.height);
      return;
    }
    roi = r;
  }
  else{
    // zoom to full image for now when zooming out
    roi = wxRect(0,0,width,height);
  }

  wxLogMessage(wxT("New ROI: (%d %d %d %d) or ((%d %d) (%d %d))"),roi.x,roi.y,roi.width,roi.height,
               roi.x,roi.x+roi.width,roi.y,roi.y+roi.height);
  UpdateData();
  img_panel->ShowCaret(false);
  img_panel->Refresh();
}

void ImageFrame::OnResize(wxSizeEvent&){
  const wxSize& s = GetClientSize();
  size_t w = s.GetWidth(), h = s.GetHeight();
  size_t wimg = (data_panels.size() == 0) ? w : (size_t)(3.0/4.0*w);
  if(wimg != img_panel->GetDisplayWidth() || h != img_panel->GetDisplayHeight()){
    //wxLogMessage(wxT("ImageFrame::OnResize display_size %d x %d"),wimg,h);
    img_panel->SetSize(0,0,wimg,h);
    img_panel->SetDisplaySize(wimg,h);
    UpdateDisplay();
  }
  for(size_t i=0; i<data_panels.size(); ++i){
    data_panels[i]->SetSize(0,0,(size_t)(1.0/4.0*w),(size_t)((float)h/data_panels.size()));
    data_panels[i]->Move(wimg,(size_t)((float)i*h/data_panels.size()));
  }
}


// image_window.cc ends here
