// jingxiushi.c 靜修室
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "靜修室");
        set("long", @LONG
這裏是全真教弟子靜修參悟道情的房間，房間很小，但收拾的幹
乾淨淨，桌椅都擺放得整整齊齊，讓人一看就心無雜念。
LONG
        );
        set("exits", ([
                "east" : __DIR__"houshan",
                "south" : __DIR__"diziju",
                "west" : __DIR__"houtang3",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/liu" : 1,
        ]));

        set("coor/x", -2730);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;

        if (dir == "east" )
        {
                if( !(fam=query("family", me)) || fam["family_name"] != "全真教" )
                {
                        if(present("liu chuxuan", environment(me)) && living(present("liu chuxuan", environment(me))))
                        {
                                return notify_fail(
"劉處玄伸手攔住你道：後面是本教祖師清修之地，" + RANK_D->query_respect(me) + "請
止步。\n");
                        }
                        else
                                return ::valid_leave(me, dir);
                }
                else
                        return ::valid_leave(me, dir);
        }
        else
                return ::valid_leave(me, dir);

}
