// Room: /d/shaolin/guangchang3.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "勤修場");
        set("long", @LONG
這是戒律院前的勤修場。這裏是全寺交通最密集的地方，只見一
隊隊僧人來來去去，身着各種服色，有的攜帶刀，槍，棍，杖等兵器，
個個身姿矯健，神態莊重。北面的大殿就是戒律院，四位僧兵持刀守
在兩側。西邊通向齋廳。
LONG );
        set("exits", ([
                "south" : __DIR__"guangchang2",
                "north" : __DIR__"guangchang4",
                "northup" : __DIR__"jlyuan",
                "west" : __DIR__"fanting",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;

        if (dir == "northup")
        {
                if( mapp(fam=query("family", me) )
                &&  fam["family_name"] == "少林派" 
                &&  fam["generation"] == 37  ) 
                        return ::valid_leave(me, dir);
                
                if( query("guilty", me) == 0
                 && query("id", me) != "sengbing" )
                {
                        return notify_fail("僧兵擋住説道：你未經許可，不能進入戒律院。\n");
                }
        }

        return ::valid_leave(me, dir);
}
