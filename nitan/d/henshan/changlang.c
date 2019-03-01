inherit ROOM;

void create()
{
          set("short","長廊");
        set("long", @LONG
這是通往客房的長廊，不遠處便是客房和廚房了。
LONG );
          set("exits",([
                      "west"      :__DIR__"zhurongdian",
                  "northeast" :__DIR__"henshan_chufang",
                  "north"     :__DIR__"kefang",
          ]));

          set("objects", ([
                  __DIR__"npc/xiangke" : 2,
          ]));
	set("coor/x", -6920);
	set("coor/y", -5490);
	set("coor/z", 40);
	setup();
          replace_program(ROOM);
}