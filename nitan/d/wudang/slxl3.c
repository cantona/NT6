inherit ROOM;

void create()
{
        set("short", "鬆林小路");
        set("long", @LONG
這是山腳鬆林中的小路，兩邊長滿參天的紅鬆樹，只能看見一線
天空。路旁有道士在奮力砍樹。西邊通向武當山門，東邊可通往解劍
巖。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "west" : __DIR__"xuanyuegate",
                "eastdown" : __DIR__"jiejianyan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -180);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}