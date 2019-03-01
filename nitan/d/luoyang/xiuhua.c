inherit ROOM;

void create()
{
        set("short", "羞花汀");
        set("long", @LONG
春月樓著名之處在這裡可略見一斑，四邊花草甚多，但唯有牡丹最勝。
那花不是尋常玉樓春之類，乃“姚黃”“魏紫”有名異品，一本價值五千。
那花正種在朱門對面，周圍以湖石攔之。其花大如丹盤，五色燦爛，光華
奪目。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"jiyuan2",
        ]));

	set("coor/x", -6980);
	set("coor/y", 2120);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}