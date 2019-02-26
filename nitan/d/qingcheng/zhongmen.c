// Room: /qingcheng/zhongmen.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "穿廊門");
        set("long", @LONG
這裏是松風觀通往後院的中門，門厚三寸，紅松銅箍，數十年猶有
松香飄蕩，和觀中香火摻和出一股出世的滋味。外派人士到此就該回頭
了。
LONG );
        set("exits", ([
                "south" : __DIR__"qiandian",
                "north" : __DIR__"zoulang1",
        ]));
        set("objects", ([
                __DIR__"npc/yu" : 1,
        ]));
        set("coor/x", -8080);
        set("coor/y", -860);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
/*        mapping myfam;
        myfam=query("family", me);
        if ((!myfam || (myfam["family_name"] != "青城派")) && (dir == "north"))
                return notify_fail("非青城弟子，到此止步吧。\n");
        else return 1;
*/
if (dir != "south" )
        {
                if( query("family/family_name", me) != "青城派" )
                {                        
                       if(present("yu renhao", environment(me)) && living(present("yu renhao", environment(me))))
                        {
                                return notify_fail(
"於人豪喝道：後面是本派重地，這位" + RANK_D->query_respect(me) + "請止步。\n");
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