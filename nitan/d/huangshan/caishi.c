// Room: /d/huangshan/caishi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "採石峰");
        set("long", @LONG
相傳是女媧採石補天所取天下山石中精英所在，山色與別山迥異，
竟似有五色，山上樹木也分外茂密，山籐蔓繞，由于遊人到鬆谷庵後多
半力竭，加之這裡山籐環繞，甚是難走，所以以無遊人到此。遠遠看見
軒轅峰，卻已無力過去。
LONG
        );
        set("exits", ([ 
                "westdown" : __DIR__"songgu",
                "east"     : __DIR__"xuanyuan",
        ]));
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -970);
        set("coor/z", 10);
        setup();
}
void init()
{
        add_action("do_chop","chop");
}

int do_chop(string arg)
{
        object obj, me = this_player();

        if(!arg || arg=="")
        {
                write("你要砍開什麼？\n");
                return 1;
        }
        if( arg == "vine" || arg == "山籐")
        {
                if( !objectp(obj=query_temp("weapon", me)) )
                {
                        write("你空著手，砍什麼砍？\n");
                        return 1;
                }
                if( query("skill_type", obj) == "sword" || 
                        query("skill_type", obj) == "blade" || 
                        query("skill_type", obj) == "axe" )
                {
                        if( !query("exits/east") )
                        {
                                set("exits/east", __DIR__"xuanyuan");
                                message_vision(sprintf("$N用手中的%s砍出一條向北的路。\n", obj->name()), me);
                                me->start_busy(1);
                        }
                        else
                                message_vision(sprintf("$N用手中的%s砍向環繞的山籐。\n",obj->name()), me);
                }
                else
                        message_vision(sprintf("$N用手中的%s向蔓繞的山籐一頓亂砍。\n",obj->name()), me);
        }
        else write("你要砍開什麼？\n");
        return 1;
}

void reset()
{
        ::reset();
        delete("exits/east");
}