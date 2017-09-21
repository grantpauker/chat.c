#include <gtk/gtk.h>
void delay(int number_of_seconds);
char *get_textview(GtkWidget *text_view);
void append_textview(GtkWidget *text_view, const gchar *text);

GtkBuilder      *builder;
GtkWidget       *window,*button,*textview,*entry;

int sent =0;
char count[5];
int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_test.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
    g_object_unref(builder);
    gtk_widget_show(window);
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
}

void clicked(){
append_textview(textview,"hey");
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
