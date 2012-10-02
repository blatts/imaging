// -*- mode: C++/lah -*-
// Time-stamp: "2010-03-03 15:04:04 srgang"

/*
  file       image_window.hh
  copyright  (c) Sebastian Blatt 2010

 */


#ifndef IMAGE_WINDOW_HH
#define IMAGE_WINDOW_HH

#include <wx/wx.h>
#include <vector>

void interpolate_color(float t, unsigned char* rgb, unsigned char* pal, size_t n);
void interpolate_color(float t, float t0, float t1, unsigned char* rgb,
                       unsigned char* pal, size_t n);

class ImagePanel : public wxPanel {
  private:
    wxBitmap img;
    wxMemoryDC imgdc;
    wxRect caret;
    bool drawing_caret;
    bool caret_display;
    bool zoom_in;
    float info_palmin;
    float info_palmax;
    unsigned char* info_palette;
    size_t info_palette_size;
    wxMemoryDC palette_mdc;
    wxBitmap palette_bmp;
    size_t palette_bmp_w;
    size_t palette_bmp_h;
    bool com_display;
    size_t com_i;
    size_t com_j;

  public:
    ImagePanel(wxFrame* parent,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos=wxDefaultPosition,
               const wxSize& size=wxDefaultSize);
    ~ImagePanel();
    void RecreateBitmap(const wxImage& new_image);
    void FreeBitmap();
    void OnPaint(wxPaintEvent&);
    void OnEraseBackground(wxEraseEvent&);
    void OnMouseLeftDown(wxMouseEvent& evt);
    void OnMouseLeftUp(wxMouseEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);

    const wxRect& GetCaret() const {return caret;}
    void ShowCaret(bool show){caret_display = show;}
    const bool ZoomingIn() const {return zoom_in;}


    void SetPaletteInfoScale(float palmin, float palmax){
      info_palmin = palmin;
      info_palmax = palmax;
    }
    void SetPaletteInfo(unsigned char* p, size_t size);
    void SetCOMMarker(size_t i, size_t j){
      com_i = i; com_j = j;
    }

    DECLARE_EVENT_TABLE()
};

DECLARE_EVENT_TYPE(wxEVT_IMAGE_PANEL,-1)


class ImageFrame : public wxFrame {
  private:
    ImagePanel* img_panel;
    long** raw_image_data;
    wxMutex* raw_image_data_mutex;
    unsigned int width;
    unsigned int height;
    float* processed_data;
    wxImage processed_image;
    wxImage disp_image;
    unsigned char* palette;
    size_t palette_size;
    float palette_min;
    float palette_max;
    float palette_min_manual;
    float palette_max_manual;
    bool palette_scale_manual;
    bool palette_scale_next_image;
    wxRect roi;
    bool kinetics;
    unsigned int n_kinetics;
    bool rotate_image;

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
    void SetKinetics(bool kinetics_on, unsigned int n_kinetics_=1);
    void SetScaleManual(bool scaleq) {palette_scale_manual = scaleq;}
    bool GetScaleManual() const {return palette_scale_manual;}
    void SetScaleNextImage() {palette_scale_next_image = true;}
    void SetScaleMin(float tmin) {palette_min_manual = tmin;}
    void SetScaleMax(float tmax) {palette_max_manual = tmax;}

    void OnCaretDone(wxCommandEvent&);

    void interpolate_image(float* t, float t0, float t1, unsigned char* rgb,
                           unsigned char* pal, size_t npal, const wxRect& palroi);
    std::vector<float> ROIStatistics(wxRect roi);

    DECLARE_EVENT_TABLE()
};



#endif // IMAGE_WINDOW_HH

// image_window.hh ends here
