// Room: /heizhao/shanlu9.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

int do_find(string arg);
void create()
{
        set("short", "山路");
        set("long", @LONG
又行了一陣，正覺唇幹口渴，忽聽遠處傳來隱隱水聲，你當即
加快腳步。空山寂寂，那水聲在山谷間激盪回響，轟轟洶洶，癒走
水聲癒大，待得走上嶺頂，只見一道白龍似的大瀑布從對面雙峰之
間奔騰而下，聲勢甚是驚人。從嶺上望下去，瀑布旁有一間草屋。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                //"northdown" : __DIR__"pubu",
                "northdown" : __DIR__"yideng1",
                "eastdown"  : __DIR__"shanlu8",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1290);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_find", "find");
        add_action("do_find", "zhao");
}

int do_find(string arg)
{
        object me;
        object *inv;
        int i;
        me=this_player();

        if( arg == "way" && query("family/master_id", me) == "yidengdashi" )
        {
                        
                inv=all_inventory(me);
                for(i=0; i<sizeof(inv); i++) {
                        if (userp(inv[i]))
                                return notify_fail("你負重太大了，沒法找路爬山。\n");
                }
                tell_object(me, "你左右看看沒人注意你，偷偷摸摸撥開樹叢溜了進去。\n");
                tell_object(me, "你從一條沒人知道的小路上了山，來到了一燈大師所在的地方。\n");
                me->move(__DIR__"yideng9");
                return 1;
        }
        return 0;
}

