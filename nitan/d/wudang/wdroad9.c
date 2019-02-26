inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁盡是陰森森的樹林。這裏
是湖北境界，據説經常有土匪出沒，不可久留。向東南去可至湖南。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "northwest" : __DIR__"sanbuguan",
                "south"     : __DIR__"wdroad10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -320);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
