inherit ROOM;

void create()
{
      set("short", "正殿");
        set("long", @LONG
這裡是峨嵋山金頂華藏庵的正殿。華藏庵規模宏大，殿內青磚舖
地，中間有普賢菩薩像，兩旁列有萬佛。正前方放一紅木供桌，陳列
香燭，以供叩拜。自此左右各有一間側殿，是接待香客的地方。南面
是通往一個大廣場。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/xin" : 1,
           __DIR__"npc/guest" : 1,
      ]));
      set("exits", ([
          "out"   : __DIR__"huacangan",
          "east"  : __DIR__"hcaeast", 
          "west"  : __DIR__"hcawest", 
          "south" : __DIR__"hcaguangchang", 
      ]));
      set("coor/x", -560);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if (dir != "out" &&
            objectp(ob = present("jingxin shitai", this_object())))
                return ob->permit_pass(me, dir);
        return ::valid_leave(me, dir);
}