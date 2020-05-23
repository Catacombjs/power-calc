

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    GtkWidget *w_ent1;
    GtkWidget *w_ent2;
    GtkWidget *w_out_d;
    GtkWidget *w_out_d_r;
    GtkWidget *w_out_n;
    GtkWidget *w_out_n_r;
    GtkWidget *w_out_all;
    GtkWidget *w_out_all_r;
    GtkWidget *w_check_1;
    GtkWidget *w_check_2;    
    GtkWidget *w_check_v;
    GtkWidget *w_off;
    
} app_widgets;


int main(int argc, char *argv[])
{
    GtkBuilder    *builder;
    GtkWidget     *window;
    app_widgets   *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "general_main"));

    // get pointers to widgets
    widgets->w_ent1 = GTK_WIDGET(gtk_builder_get_object(builder, "ent1"));
    widgets->w_ent2 = GTK_WIDGET(gtk_builder_get_object(builder, "ent2"));
   widgets->w_out_d = GTK_WIDGET(gtk_builder_get_object(builder, "out_d"));
   widgets->w_out_n = GTK_WIDGET(gtk_builder_get_object(builder, "outn"));
  widgets->w_out_all = GTK_WIDGET(gtk_builder_get_object(builder, "out_all"));
widgets->w_out_d_r = GTK_WIDGET(gtk_builder_get_object(builder, "out_d_r"));
widgets->w_out_n_r = GTK_WIDGET(gtk_builder_get_object(builder, "out_n_r"));
widgets->w_out_all_r = GTK_WIDGET(gtk_builder_get_object(builder, "out_all_r"));
widgets->w_check_1 = GTK_WIDGET(gtk_builder_get_object(builder, "check_1"));
widgets->w_check_2 = GTK_WIDGET(gtk_builder_get_object(builder, "check_2"));
widgets->w_check_v = GTK_WIDGET(gtk_builder_get_object(builder, "check_v"));
widgets->w_off = GTK_WIDGET(gtk_builder_get_object(builder, "off"));


    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

void on_mybtn_clicked(GtkButton *button, app_widgets  *app_wdgts)
{
  char buffer[16];
    float num1 =(float) atof((char*) gtk_entry_get_text(GTK_ENTRY (app_wdgts->w_ent1 )) );
  float  num2 = atof((char*) gtk_entry_get_text(GTK_ENTRY (app_wdgts->w_ent2 )));
float  num_day = atof((char*) gtk_entry_get_text(GTK_ENTRY (app_wdgts->w_check_1 )));
float  num_night = atof((char*) gtk_entry_get_text(GTK_ENTRY (app_wdgts->w_check_2)));

if(!gtk_toggle_button_get_active ((GtkToggleButton *) (app_wdgts->w_check_v ))) {


float rez_d = (float)16.0*num1*num2;
   snprintf(buffer, sizeof(buffer), "%.2f" , rez_d );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_d), buffer);
snprintf(buffer, sizeof(buffer), "%.2f" ,rez_d*num_day );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_d_r), buffer);

  float rez_n = (float)8.0*num1*num2;
   snprintf(buffer, sizeof(buffer), "%.2f" , rez_n );
    gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_n), buffer );
snprintf(buffer, sizeof(buffer), "%.2f" , rez_n*num_night );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_n_r), buffer);

float rez_all = (float)(rez_d +rez_n);
   snprintf(buffer, sizeof(buffer), "%.2f" , rez_all );
    gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_all), buffer );
snprintf(buffer, sizeof(buffer), "%.2f" ,rez_d*num_day + rez_n*num_night );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_all_r), buffer);

}else {

float rez_d = (float)24.0*num1;
snprintf(buffer, sizeof(buffer), "%.2f" ,rez_d*num2*num_day );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_out_all_r), buffer);

}

}

void on_check_data_toggled(GtkToggleButton *button,  app_widgets *app_wdgts)
{
if( gtk_toggle_button_get_active(button) ) {
gtk_widget_set_sensitive(app_wdgts-> w_check_1 ,TRUE );
gtk_widget_set_sensitive(app_wdgts-> w_check_2 ,TRUE );
}
else {
gtk_widget_set_sensitive(app_wdgts-> w_check_1 ,FALSE );
gtk_widget_set_sensitive(app_wdgts-> w_check_2 ,FALSE );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_check_1), "4.49");
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_check_2), "2.43");

}

}

void on_check_v_toggled(GtkToggleButton *button,  app_widgets *app_wdgts)
{
if( gtk_toggle_button_get_active(button) ) {
gtk_widget_set_visible(app_wdgts-> w_check_2 ,FALSE );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_check_1), "4.27");
}
else {
gtk_widget_set_visible(app_wdgts-> w_check_2 ,TRUE );
gtk_entry_set_text( GTK_ENTRY(app_wdgts->w_check_1), "4.49");
}

}

// called when window is closed
void on_general_main_destroy()
{
    gtk_main_quit();
}
