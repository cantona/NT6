// Room: /d/huangshan/shizi.c
// Last Modified by winder on Sep. 27 2001
inherit ROOM;
void create()
{
        set("short", "獅子峯");
        set("long", @LONG
遠像是一頭卧獅，頭西尾東橫卧於前。上面勝景無數，獅子林，麒
麟，寶塔等奇鬆，蒲團，鳳凰等古柏都是罕見的美景，所以向有“沒到
獅子峯，不見黃山蹤”的盛譽。尤以北方的清涼台更為出名，向來是遊
人必去之所。
LONG
        );
        set("exits", ([ 
                "northdown" : __DIR__"qingliang",
                "southdown" : __DIR__"paiyun",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1010);
        set("coor/z", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        object ob;

        if( userp(me) && dir=="west" &&
                (ob=present("bai hong", this_object()) ||
                ob=present("bai huan", this_object())) &&
                query("bellicosity", me)>50 )
                return notify_fail(ob->name()+"説道：請留步！\n");
        return 1;
}
void reset()
{
        object me,me2;

        :: reset();
        me2=present("bai huan", this_object());
        me=present("bai hong", this_object());
        if(me) me->dismiss_team();
        if(me2) me2->dismiss_team();
        if(me && me2) me->add_team_member(me2);
}