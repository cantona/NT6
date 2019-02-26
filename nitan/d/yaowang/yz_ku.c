inherit ROOM;

void create()
{
        set("short", "藥材庫");
        set("long", @LONG
這是一間巨大的瓦房，房子裏被直到屋頂的大木架子佔滿了，
一股難聞的氣味讓人渾身不舒服，門口的竹椅上坐着一位中年人。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"yz_xiaoyuan",
]));

        set("objects", ([
        "/kungfu/class/yaowang/murong" : 1,
]));
        setup();
        replace_program(ROOM);
}
