// -*- mode: C++/lah -*-
// Time-stamp: "2010-03-08 11:04:54 srgang"

/*
  file       image_window.cc
  copyright  (c) Sebastian Blatt 2010

 */

#include "gui_ids.hh"
#include "image_window.hh"

#include <algorithm>
#include <sstream>



void interpolate_color(float t, unsigned char* rgb, unsigned char* pal, size_t n){
  float x = t*(n-1), z=0;
  size_t j = floor(x);
  if(j>=n){j=n-1;}
  x -= j;
  j *= 3;
  z = pal[j];   rgb[0] = z + (unsigned char)((pal[j+3]-z) * x);
  z = pal[j+1]; rgb[1] = z + (unsigned char)((pal[j+4]-z) * x);
  z = pal[j+2]; rgb[2] = z + (unsigned char)((pal[j+5]-z) * x);
}

void interpolate_color(float t, float t0, float t1,
                       unsigned char* rgb, unsigned char* pal, size_t n)
{
  if(t<t0)      {interpolate_color(0.0f,rgb,pal,n);}
  else if(t>t1) {interpolate_color(1.0f,rgb,pal,n);}
  else          {interpolate_color((t-t0)/(t1-t0),rgb,pal,n);}
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
                       const wxSize& size)
: wxPanel(parent,id,pos,size),
  img(1024,1024),
  caret(0,0,0,0),
  drawing_caret(false),
  caret_display(false),
  zoom_in(true),
  info_palmin(0),
  info_palmax(0),
  info_palette(NULL),
  info_palette_size(0),
  palette_mdc(),
  palette_bmp(),
  palette_bmp_w(1014),
  palette_bmp_h(10),
  com_display(false),
  com_i(0),
  com_j(0)
{
  imgdc.SelectObject(img);
  palette_bmp.Create(palette_bmp_w,palette_bmp_h);
  palette_mdc.SelectObject(palette_bmp);
}

ImagePanel::~ImagePanel(){
  FreeBitmap();
}

void ImagePanel::SetPaletteInfo(unsigned char* p, size_t size){
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

void ImagePanel::OnPaint(wxPaintEvent&){
  wxPaintDC dc(this);
  wxCoord w,h;
  dc.GetSize(&w,&h);
  dc.Blit(0,0,w,h,&imgdc,0,0);
  if(info_palette){
    dc.Blit(5,5,palette_bmp_w,palette_bmp_h,&palette_mdc,0,0);

    wxFont fnt = wxFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL,false,"",wxFONTENCODING_DEFAULT);
    dc.SetFont(fnt);
    dc.SetTextBackground(*wxBLACK);
    dc.SetTextForeground(*wxGREEN);

    std::ostringstream os;
    os.setf(std::ios::fixed);
    os.setf(std::ios::showpoint);

    for(size_t i=0; i<info_palette_size; ++i){
      int x = 5 + i * ((float)palette_bmp_w) / (info_palette_size-1);
      os.precision(1);
      os << info_palmin + (info_palmax-info_palmin)/(info_palette_size-1) * i;
      wxSize s = dc.GetTextExtent(os.str().c_str());
      if(i>0){ x -= s.GetWidth()/2; }
      if(i==info_palette_size-1) { x -= s.GetWidth()/2; }
      dc.DrawText(os.str().c_str(),x,5+palette_bmp_h+5);
      os.str("");
    }
  }
  if(com_display){
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawCircle(com_i,com_j,5);
  }
  if(caret_display){
    dc.SetPen(*wxGREEN_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(caret.x,caret.y,caret.width,caret.height);
  }
}

void ImagePanel::OnEraseBackground(wxEraseEvent&){
  // Empty. Do not erase background since OnPaint always draws the
  // whole control. This prevents flickering.
}

void ImagePanel::RecreateBitmap(const wxImage& new_image){
  FreeBitmap();
  img = wxBitmap(new_image);
  imgdc.SelectObject(img);
  Refresh();
}

void ImagePanel::FreeBitmap(){
  imgdc.SelectObject(wxNullBitmap);
}

void ImagePanel::OnMouseLeftDown(wxMouseEvent& evt){
  //wxLogMessage("OnLeftDown %d,%d",evt.GetX(),evt.GetY());
  caret.x = evt.GetX();
  caret.y = evt.GetY();
  drawing_caret = true;
  caret_display = true;
  zoom_in = true;
}

void ImagePanel::OnMouseLeftUp(wxMouseEvent& evt){
  wxCoord x = evt.GetX(), y = evt.GetY();
  //wxLogMessage("OnLeftDown %d,%d",x,y);
  if(drawing_caret){
    caret.width = x - caret.x;
    caret.height = y - caret.y;
    //wxLogMessage("Caret done : %d %d %d %d",caret.x,caret.y,caret.width,caret.height);
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



BEGIN_EVENT_TABLE(ImageFrame,wxFrame)
EVT_COMMAND(ID_IMAGE_WINDOW_CARET_DONE,wxEVT_IMAGE_PANEL,ImageFrame::OnCaretDone)
END_EVENT_TABLE()

ImageFrame::ImageFrame(wxFrame* parent, const wxString& title,
                       const wxPoint& pos, const wxSize& size,
                       long** raw_image_data_,
                       wxMutex* raw_image_data_mutex_,
                       unsigned int width_, unsigned int height_
                      )
: wxFrame(parent,-1,title,pos,size,wxRESIZE_BORDER|wxCAPTION),
  img_panel(NULL),
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
  kinetics(false),
  n_kinetics(1),
  rotate_image(false)
{
  img_panel = new ImagePanel(this,wxNewId());
  processed_data = new float[width*height];
  memset(processed_data,0,sizeof(float)*width*height);
  palette_size = 6;
  palette = new unsigned char[3*palette_size];
  memset(palette,0,sizeof(unsigned char)*3*palette_size);
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
  img_panel->SetPaletteInfo(palette,palette_size);
}

ImageFrame::~ImageFrame(){
  if(processed_data){
    delete[] processed_data;
    processed_data = NULL;
  }
  if(palette){
    delete[] palette;
    palette =NULL;
    palette_size= 0;
  }
}


void ImageFrame::UpdateData(){
  size_t area = width*height;
  size_t subarea = width*(height/n_kinetics);
  float tmin = 0, tmax = 0, t = 0;
  {
    wxMutexLocker lock(*raw_image_data_mutex);
    if(!kinetics){
      tmin = tmax = **raw_image_data;
      for(size_t i=0; i<area; ++i){
        t = (*raw_image_data)[i];
        if(t > tmax){ tmax = t; }
        if(t < tmin){ tmin = t; }
        processed_data[i] = t;
      }
    }
    else{
      memset(processed_data,0,sizeof(float)*area);
      long* idark = (*raw_image_data) + 0 * subarea;
      long* ishadow = (*raw_image_data) + 1 * subarea;
      long* ilight = (*raw_image_data) + 2 * subarea;
      float* od = processed_data + subarea;
      float a=0, b=0;
      for(size_t i=0; i<subarea; ++i){
        a = std::max(logf(std::max((float)(ilight[i]-idark[i]),0.0f)),-1.0f);
        b = std::max(logf(std::max((float)(ishadow[i]-idark[i]),0.0f)),-1.0f);
        //t = std::max(a-b,0.0f);
        t = a - b;
        if(t > tmax){ tmax = t; }
        if(t < tmin){ tmin = t; }
        od[i] = t;
      }
    }
  }
  //wxLogMessage("Image min: %f, max: %f",tmin,tmax);

  wxRect total_image(0,0,width,height);
  if(kinetics){
    total_image = wxRect(0,height/n_kinetics,width,height/n_kinetics);
  }
  wxRect palroi = total_image;
  palroi = palroi.Intersect(roi);
  //wxLogMessage("totalimg : %d %d %d %d",total_image.x,total_image.y,
  //             total_image.width,total_image.height);
  //wxLogMessage("palroi : %d %d %d %d",palroi.x,palroi.y,palroi.width,palroi.height);

  std::vector<float> roi_tot = ROIStatistics(total_image);
  std::vector<float> roi_stat = ROIStatistics(palroi);
  //wxLogMessage("Total image [min,max] = [%f, %f]",roi_tot[0],roi_tot[1]);
  //wxLogMessage("ROI [min,max] = [%f, %f]",roi_stat[0],roi_stat[1]);


  img_panel->SetCOMMarker(palroi.x+floor(roi_stat[6]+.5),palroi.y+floor(roi_stat[7]+.5));

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


  interpolate_image(processed_data,palette_min,palette_max,
                    processed_image.GetData(),palette,palette_size,palroi);

  unsigned int xw = (roi.width>=roi.height)?width:((float)roi.width)/roi.height*width;
  unsigned int yw = (roi.width>=roi.height)?((float)roi.height)/roi.width*height:height;
  //wxLogMessage("xw : %d, yw: %d",xw,yw);
  disp_image = processed_image.GetSubImage(roi);

  if(rotate_image){
    disp_image = disp_image.Rotate90();
    std::swap(xw,yw);
    std::swap(width,height);
  }
  disp_image.Rescale(xw,yw);
  disp_image.Resize(wxSize(width,height),wxPoint((xw==width)?0:((width-xw)/2),
                                                 (yw==height)?0:((height-yw)/2)));
  if(rotate_image){
    std::swap(width,height);
  }
  img_panel->RecreateBitmap(disp_image);
}


void ImageFrame::interpolate_image(float* t, float t0, float t1, unsigned char* rgb,
                                   unsigned char* pal, size_t npal, const wxRect& palroi)
{
  memset(rgb,0,sizeof(unsigned char)*3*width*height);
  size_t idx = 0;
  for(int i=0; i<palroi.width; ++i){
    for(int j=0; j<palroi.height; ++j){
      idx = (palroi.y + j)*width + (palroi.x+i);
      interpolate_color(t[idx],t0,t1,&(rgb[3*idx]),pal,npal);
    }
  }
}

std::vector<float> ImageFrame::ROIStatistics(wxRect roi){
  size_t i=0, j=0, w=roi.width, h=roi.height;
  float t=0,tmin=0, tmax=0;
  float m1=0, cmx=0, cmy=0;

  size_t subarea = width*(height/n_kinetics);
  float* od = (kinetics)?(processed_data+subarea):processed_data;

  tmin = tmax = od[0];
  for(i=0; i<w; ++i){
    for(j=0; j<h; ++j){
      t = od[(roi.y+j)*width + (roi.x+i)];
      if(t<tmin){ tmin = t; }
      if(t>tmax){ tmax = t; }
      m1 += t;
      cmx += i*t;
      cmy += j*t;
    }
  }
  std::vector<float> rc(8);
  rc[0] = tmin; // minimum
  rc[1] = tmax; // maximum
  rc[2] = m1; // integrated
  rc[3] = width*height>0 ? m1/(width*height) : 0; // mean
  //rc[4] = width*height>1 ? sqrt(m2/(width*height-1)) : 0; // variance
  rc[5] = 0;
  rc[6] = cmx / m1; // center of mass x
  rc[7] = cmy / m1; // center of mass y
  return rc;
}

void ImageFrame::OnCaretDone(wxCommandEvent&){
  wxRect r = img_panel->GetCaret();
  if(rotate_image){
    std::swap(width,height);
  }
  if(img_panel->ZoomingIn()){
    if(r.width == 0 || r.height == 0){
      if(rotate_image){
        std::swap(width,height);
      }
      return;
    }

    // Normalize Rectangle and crop to currently displayed area

    // coordinates of current roi in display frame
    unsigned int xw = (roi.width>=roi.height)?width:((float)roi.width)/roi.height*width;
    unsigned int yw = (roi.width>=roi.height)?((float)roi.height)/roi.width*height:height;
    unsigned int x0 = (xw==width)?0:((width-xw)/2);
    unsigned int y0 = (yw==height)?0:((height-yw)/2);

    // fix negative width or height
    if(r.width < 0){r.x += r.width; r.width = -r.width;}
    if(r.height < 0){r.y += r.height; r.height = -r.height;}
    // fix negative x,y position by cropping
    if(r.x < 0){r.width += r.x; r.x = 0;}
    if(r.y < 0){r.height += r.y; r.y = 0;}
    // crop width, height
    if(r.width > (int)width){r.width = width;}
    if(r.height > (int)height){r.height = height;}

    wxRect rdisp(x0,y0,xw,yw);
    r.Intersect(rdisp);

    // Calculate new roi with respect to old roi

    // coordinates of caret in full image frame
    r.x = roi.x + ((float)r.x)/xw*roi.width;
    r.y = roi.y + ((float)r.y)/yw*roi.height;
    r.width = ((float)r.width)/xw*roi.width;
    r.height = ((float)r.height)/yw*roi.height;

    if(r.width == 0 || r.height == 0){
      if(rotate_image){
        std::swap(width,height);
      }
      return;
    }


    roi = r;
  }
  else{
    // zoom to full image for now when zooming out
    roi = wxRect(0,0,width,height);
  }

  if(rotate_image){
    std::swap(width,height);
  }

  wxLogMessage("New ROI: %d %d %d %d",roi.x,roi.y,roi.width,roi.height);
  UpdateData();
  img_panel->ShowCaret(false);
  img_panel->Refresh();
}

void ImageFrame::SetKinetics(bool kinetics_on, unsigned int n_kinetics_){
  kinetics = kinetics_on;
  n_kinetics = n_kinetics_;
}


// image_window.cc ends here
