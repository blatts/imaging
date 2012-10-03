// -*- mode: C++/lah -*-
// Time-stamp: "2010-04-02 12:51:27 srgang"

/*
  file       image_window.hh
  copyright  (c) Sebastian Blatt 2010

 */


#ifndef IMAGE_WINDOW_HH
#define IMAGE_WINDOW_HH

#include <wx/wx.h>
#include <vector>

// Helper functions to interpolate floating point data into RGB values
// using a palette.
void interpolate_color(float t, unsigned char* rgb, unsigned char* pal, size_t n);
void interpolate_color(float t, float t0, float t1, unsigned char* rgb,
                       unsigned char* pal, size_t n);

class Axes {
  private:
    size_t display_pad_w; // offset any drawing operation from dc horizontal borders by this
    size_t display_pad_h; // offset any drawing operation from dc vertical borders by this
    size_t axes_padding; // in addition, use this padding to make room for ticks and labels
    bool ticks_outside; // ticks extend outside or inside of frame
    size_t major_ticks; // separate axes into this many major ticks
    size_t minor_ticks; // minor ticks per major tick
    size_t major_tick_length; // major tick length in px
    size_t minor_tick_length; // minor tick length in px
    wxRect axes_extent; // axes labels cover this rectangle

  public:
    Axes();
    ~Axes();

    // draw axes into DC using current pen and font
    void Draw(wxDC& dc, size_t client_width, size_t client_height);
};


/*
  Region of interest display panel for ImageFrame class below. Any
  coordinates in this class are in the _display_ frame! Conversions
  accounting for cropping of ROI, rotation, scaling, translation are
  taken into account in ImageFrame only!

  This makes mouse interactions and display easy, but means that all
  actual data interaction has to be handled by the parent ImageFrame!

 */
class ImagePanel : public wxPanel {
  private:
    size_t display_width; // display panel width
    size_t display_height; // display panel height
    wxRect display_rect; // actual display area for image
    size_t display_pad_w; // horizontal padding for display_rect
    size_t display_pad_h; // vertical padding for display_rect

    wxBitmap bmp; // holds rgb image data, dimension (display_width x display_height)
    wxMemoryDC bmpdc; // holds img for blitting

    wxRect caret; // caret _in_display_coordinates_ for selecting new ROI
    wxRect caret_final; // final caret in display coordinates, accounting for padding, etc.
    bool drawing_caret; // true while mouse is dragged
    bool caret_display; // display caret?
    bool zoom_in;  // true while not showing full image
    bool select_marker; // true while dragging a caret to select marker region

    bool palette_display; // display palette
    float info_palmin; // float value corresponding to palette mininum
    float info_palmax; // float value corresponding to palette maximum
    unsigned char* info_palette; // pointer to palette color information
    size_t info_palette_size; // number of colors in palette
    wxMemoryDC palette_mdc; // holds palette gradient bitmap
    wxBitmap palette_bmp; // palette gradient bitmap
    size_t palette_bmp_w; // palette gradient bitmap width
    size_t palette_bmp_h; // palette gradient bitmap height

    wxRect info_data_roi; // data frame rectangle to displayed frame
    wxRect info_display_roi; // display frame corresponding to info_data_roi
    bool axes_display; // display data frame coordinate axes?
    size_t axes_offset; // axes distance from outer frame in px
    size_t major_ticks; // number of labelled ticks
    size_t minor_ticks; // number of unlabelled ticks between major ticks
    size_t major_tick_length; // length of major tick mark
    size_t minor_tick_length; // length of minor tick mark

    bool com_display; // show center of mass marker?
    wxPoint com; // marker position _in_display_coordinates_

    bool statistics_display; // show ROI statistics?
    std::vector<float>* roi_stat; // statistics vector
    std::vector<wxString>* roi_labels; // labels for statistics vector
    size_t statistics_x0; // x position of statistics output top left
    size_t statistics_y0; // y position of statistics output top left

    void draw_axes(wxDC& dc);
    void draw_palette_info(wxDC& dc);
    void draw_statistics_info(wxDC& dc);

  public:
    ImagePanel(wxFrame* parent,
               wxWindowID id,
               const wxPoint& pos,
               const wxSize& size);
    ~ImagePanel();

    void SetDisplaySize(size_t display_width_, size_t display_height_);
    size_t GetDisplayWidth() const { return display_rect.width; }
    size_t GetDisplayHeight() const { return display_rect.height; }
    void SetDataROI(const wxRect& roi){ info_data_roi = roi; }
    void SetDisplayROI(const wxRect& roi){ info_display_roi = roi;}

    void SetPaletteInfo(unsigned char* p, size_t size);
    void SetPaletteInfoScale(float palmin, float palmax){
      info_palmin = palmin;
      info_palmax = palmax;
    }

    void SetCOMMarker(const wxPoint& p){
      com = p + wxPoint(display_pad_w,display_pad_h);
    }

    void SetROIStatistics(std::vector<float>* roi_stat_,std::vector<wxString>* roi_labels_){
      roi_stat = roi_stat_;
      roi_labels = roi_labels_;
    }

    void OnPaint(wxPaintEvent&);

    // Empty. Do not erase background since OnPaint always draws the
    // whole control. This prevents flickering.
    void OnEraseBackground(wxEraseEvent&){}

    void RecreateBitmap(const wxImage& new_image);
    void FreeBitmap();

    void OnMouseLeftDown(wxMouseEvent& evt);
    void OnMouseLeftUp(wxMouseEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    const wxRect& GetCaret() const {return caret_final;}
    void ShowCaret(bool show){caret_display = show;}
    const bool ZoomingIn() const {return zoom_in;}


    DECLARE_EVENT_TABLE()
};

DECLARE_EVENT_TYPE(wxEVT_IMAGE_PANEL,-1)


class DataPanel : public wxPanel {
  private:
    size_t padding_w;
    size_t padding_h;


  public:
    DataPanel(wxFrame* parent,
              wxWindowID id,
              const wxPoint& pos,
              const wxSize& size
             );
    ~DataPanel();

    void OnPaint(wxPaintEvent&);


    DECLARE_EVENT_TABLE()
};


/*
  A wxFrame based class for displaying integer image data in false
  color.

 */
class ImageFrame : public wxFrame {
  private:
    // wxPanel based class to handle user interactions and display the
    // image data.
    ImagePanel* img_panel;

    // data panels for time series of statistical data
    std::vector<DataPanel*> data_panels;

    long** raw_image_data; // pointer to raw integer image data
    wxMutex* raw_image_data_mutex; // raw data needs mutex protected access!
    unsigned int width; // image data width
    unsigned int height; // image data height

    float* processed_data; // integer data -> processed floating point data
    wxImage processed_image; // processed floating point data -> rgb image data
    wxImage disp_image; // cropped, rotated, rescaled sub image of processed_image for display

    unsigned char* palette; // palette color information
    size_t palette_size; // number of colors in palette
    float palette_min; // floating point value corresponding to palette minimum
    float palette_max; // floating point value corresponding to palette maximum
    float palette_min_manual; // manual setting for palette minimum
    float palette_max_manual; // manual setting for palette maximum
    bool palette_scale_manual; // use manual palette scale?
    bool palette_scale_next_image; // autoscale palette to next image?

    wxRect roi; // Region Of Interest rectangle
    std::vector<float> roi_stat; // ROI statistics
    std::vector<wxString> roi_labels; // ROI statistics labels
    float display_frame_scale_x; // X scaling factor between data and display frames
    float display_frame_scale_y; // Y scaling factor between data and display frames
    int display_frame_tr_x; // X translation to center data in display frame
    int display_frame_tr_y; // Y translation to center data in display frame

    bool kinetics; // using kinetics mode?
    unsigned int n_kinetics; // number of kinetics sub images


    void free_palette();
    void create_palette();
    void interpolate_image(float* t, float t0, float t1, unsigned char* rgb,
                           unsigned char* pal, size_t npal, const wxRect& palroi);
    bool process_raw_data();
    void roi_statistics(const wxRect& roi, std::vector<float>& roi_stat);
    wxPoint data_frame_to_display_frame(const wxPoint& p);
    wxPoint display_frame_to_data_frame(const wxPoint& p);

  public:
    ImageFrame(wxFrame* parent,
               const wxString& title,
               const wxPoint& pos,
               const wxSize& size,
               long** raw_image_data_,
               wxMutex* raw_image_data_mutex_,
               unsigned int width_,
               unsigned int height_
              );

    ~ImageFrame();

    void UpdateData();
    void UpdateDisplay();
    void UpdateMarkers(const wxRect& roi, const std::vector<float>& stat);
    void OnCaretDone(wxCommandEvent&);
    void OnResize(wxSizeEvent&);


    void SetKinetics(bool kinetics_on, unsigned int n_kinetics_=1){
      kinetics = kinetics_on; n_kinetics = n_kinetics_;
    }
    void SetScaleManual(bool scaleq) {palette_scale_manual = scaleq;}
    bool GetScaleManual() const {return palette_scale_manual;}
    void SetScaleNextImage() {palette_scale_next_image = true;}
    void SetScaleMin(float tmin) {palette_min_manual = tmin;}
    void SetScaleMax(float tmax) {palette_max_manual = tmax;}

    DECLARE_EVENT_TABLE()

};



#endif // IMAGE_WINDOW_HH

// image_window.hh ends here
