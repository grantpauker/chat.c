#include <gtk/gtk.h>

void delay(int number_of_seconds);
char *get_textview(GtkWidget *text_view);
void append_textview(GtkWidget *text_view, const gchar *text);
void scroll_bottom(GtkWidget *scroll_win);
void scroll_top(GtkWidget *scroll_win);
int cfileexists(const char * filename);

GtkBuilder  *builder,*chat_window,*name_window,*chat_button,*name_button,*name_entry,*chat_view,*chat_entry,*scrolled_window;

char name[255];
char msg[255];

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "gui_properties.glade", NULL);
    name_window = GTK_WIDGET(gtk_builder_get_object(builder, "name_window"));
    name_button = GTK_WIDGET(gtk_builder_get_object(builder, "name_button"));
    name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "name_entry"));

    chat_window = GTK_WIDGET(gtk_builder_get_object(builder, "chat_window"));
    chat_button = GTK_WIDGET(gtk_builder_get_object(builder, "chat_button"));
    chat_entry = GTK_WIDGET(gtk_builder_get_object(builder, "chat_entry"));
    chat_view = GTK_WIDGET(gtk_builder_get_object(builder, "chat_view"));
    scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled_window"));

    gtk_builder_connect_signals(builder, NULL);

    if(!cfileexists("name.txt")) {
        gtk_widget_show(name_window);
        while(!cfileexists("name.txt")) {
            gtk_main_iteration();
        }
    }

    gtk_widget_destroy (name_window);
    gtk_widget_show(chat_window);

    FILE *fname;
    fname = fopen("name.txt", "r");
    fgets(name,255,(FILE*)fname);
    fclose(fname);
    printf("%s\n",name);
    sprintf(name, "%s: ", name);

    FILE *fchat;
    fchat = fopen("chat_data.txt", "r");
    while( fgets(msg,255,(FILE*)fchat) ) {
        append_textview(chat_view,msg);
    }
    fclose(fchat);

    scroll_bottom(chat_view);

    gtk_main();
    return 0;
}

int cfileexists(const char * filename) {
    FILE *file;
    if (file = fopen(filename, "r")) {
        fclose(file);
        return 1;
    }
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

void append_textview(GtkWidget *text_view, const gchar *text) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    GtkTextMark *mark = gtk_text_buffer_get_insert (buffer);
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    gtk_text_buffer_insert (buffer, &iter, text, -1);
    scroll_bottom(chat_view);
}

void scroll_top(GtkWidget *scroll_win) {
    GtkAdjustment *verticalAdjust;
    verticalAdjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll_win));
    double adjust =gtk_adjustment_get_lower(verticalAdjust);
    gtk_adjustment_set_value (verticalAdjust, adjust);
    gtk_scrolled_window_set_vadjustment (GTK_SCROLLED_WINDOW(scroll_win), verticalAdjust);
}

void scroll_bottom(GtkWidget *text_view) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(text_view),gtk_text_buffer_get_insert(buffer), 0.0, TRUE, 0.5, 1);
}

void button_clicked() {
    FILE *fchat;
    fchat = fopen("chat_data.txt", "a");
    fprintf(fchat, "%s%s\n",name,gtk_entry_get_text (chat_entry));
    fclose(fchat);
    append_textview(chat_view,"\n");
    append_textview(chat_view,name);
    append_textview(chat_view,gtk_entry_get_text (chat_entry));
}
void on_window_main_destroy() {
    gtk_main_quit();
}

void picked() {
    FILE* fname = fopen("name.txt", "a");
    fprintf(fname, "%s",gtk_entry_get_text(name_entry));
    fclose(fname);
    gtk_main_quit();
}

void delay(int number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds) ;
}
