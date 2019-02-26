inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裏仍然是後院，西面不時傳來馬嘶聲，你看過去，那裏
是個馬房，東面屋子裏也是吵吵的，好像是鋸木頭的聲音。
LONG);
        set("no_fight", 1);
        set("exits", ([
              "west" : __DIR__"guofu_mafang",
              "east" : __DIR__"guofu_mufang",
              "south" : __DIR__"guofu_houyuan",
              "north" : __DIR__"guofu_houyuan3",

        ]));
        set("outdoors", "wuguan");
        setup();
        replace_program(ROOM);
}
