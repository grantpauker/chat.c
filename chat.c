#include <gtk/gtk.h>
void delay(int number_of_seconds);
char *get_textview(GtkWidget *text_view);
void append_textview(GtkWidget *text_view, const gchar *text);
void scroll_bottom(GtkWidget *scroll_win);
void scroll_top(GtkWidget *scroll_win);
GtkBuilder      *builder;
GtkWidget       *window;
GtkWidget       *button;
GtkWidget       *textview;
GtkWidget       *entry;
GtkWidget       *scrolled_win;
  GtkAdjustment *verticalAdjust;
FILE *fp;
char count[5];
char msg[255];
int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "gui_properties.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
    scrolled_win = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled_win"));


    gtk_widget_show(window);
    gtk_widget_show(scrolled_win);
    gtk_widget_show(textview);
    fp = fopen("chat_data.txt", "r");
    while( fgets(msg,255,(FILE*)fp) ){
      append_textview(textview,msg);
    }
    fclose(fp);

   scroll_bottom(textview);



    gtk_main();

    return 0;

}

char *get_textview(GtkWidget *text_view) {
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
    gchar *text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    return text;
}

void append_textview(GtkWidget *text_view, const gchar *text){
  GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
  GtkTextMark *mark = gtk_text_buffer_get_insert (buffer);
  GtkTextIter iter;
   gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
   gtk_text_buffer_insert (buffer, &iter, text, -1);
   scroll_bottom(textview);
}


void test(){

}

void scroll_top(GtkWidget *scroll_win){
  verticalAdjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll_win));
  double adjust =gtk_adjustment_get_lower(verticalAdjust);

  gtk_adjustment_set_value (verticalAdjust, adjust);
  gtk_scrolled_window_set_vadjustment (GTK_SCROLLED_WINDOW(scroll_win), verticalAdjust);
}
void scroll_bottom(GtkWidget *text_view){
  GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
  gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(text_view),gtk_text_buffer_get_insert(buffer), 0.0, TRUE, 0.5, 1);

}
void button_clicked(){

fp = fopen("chat_data.txt", "a");
fprintf(fp, "%s\n",gtk_entry_get_text (entry));
fclose(fp);
append_textview(textview,"\n");
append_textview(textview,gtk_entry_get_text (entry));

}
void on_window_main_destroy()
{
    gtk_main_quit();
}
void delay(int number_of_seconds)
{
        int milli_seconds = 1000 * number_of_seconds;
        clock_t start_time = clock();
        while (clock() < start_time + milli_seconds) ;
}
