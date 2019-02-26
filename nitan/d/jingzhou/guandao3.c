inherit ROOM;

void create()
{
        set("short", "青石道" );
        set("long", @LONG
接近荊州，路由黃土變成了青石鋪路，兩旁漸漸可以看見一些農
舍，農田肥沃，稻香四飄。古稱荊州為軍事要地，地理為其一，肥沃
為其二啊！往西望去，可見荊州的城樓了。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "north": __DIR__"caodi",
                  "east" : __DIR__"guandao2",
                  "west" : __DIR__"jzdongmen",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7060);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}