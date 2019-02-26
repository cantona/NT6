#include <ansi.h>
inherit ROOM; 

int do_knock(string arg);

void create()
{
        set("short","忘憂園");
        set("long",
"你處在一個植滿茶花的花園裏，雖然還不是開花的時節，但是那些生\n"
"機勃勃的茶樹，不禁讓你感到心神清爽。草叢裏有些小蟲子正唧喁唧喁地\n"
"叫得正歡。\n");
        set("outdoors", "silu"); 
        set("exits",([ 
                "south"  : "/d/xingxiu/jiayuguan",
        ]));
        setup();
} 

void init()
{
        add_action("do_knock","knock");
}

int do_knock(string arg)
{ 
        object *member;
        int i;
        object env;
        string *ips;

        member = this_player()->query_team();
       
        if (!arg || arg != "spiritgate")
        {
                return notify_fail("你要敲什麼？\n");
        }
        
        if( sizeof(member) != 4 )
                return notify_fail(HIG"如果隊中成員數目不是正好為八之半，精靈之門不會開啟。\n"NOR);

        if( ! this_player()->is_team_leader() )
                return notify_fail(HIG"隊中成員中只有隊長才能開啟精靈之門。\n"NOR);

        env = environment(this_player());
        ips = ({ query_ip_number(this_player()) });
        for(i=0;i<sizeof(member);i++)
        {
                if (environment(member[i]) != env)
                        return notify_fail("你隊中成員還有沒有來齊的。\n");

                if( query("combat_exp", member[i])<2000000 )
                        return notify_fail("隊中成員裏有經驗能力太低的,你們是進不了精靈界的。\n");
                        
                if( time()-query("boss/dragon", member[i])<3600 )
                        return notify_fail(HIG "隊中成員裏有離上次屠龍時間不足一個小時，精靈之門不會開啟。\n" NOR);
        
                if (member_array(query_ip_number(member[i]), ips) == -1)
                        ips += ({ query_ip_number(member[i]) });
        }
/*
        if (sizeof(ips) < 4)
                return notify_fail(HIG"隊中成員中只有 " + sizeof(ips) + " IP地址的人，精靈之門不會開啟。\n"NOR);
*/

        for(i=0;i<sizeof(member);i++)
        {
                member[i]->move(__DIR__"spirit1"); 
                set("fighter", 0, member[i]);
                set("mark/diary", 0, member[i]);
                set("boss/dragon", time(), member[i]);
                set_temp("m_success/初級", 0, member[i]);
                set_temp("m_success/幻影", 0, member[i]);
                set_temp("m_success/孽龍", 0, member[i]);
                set_temp("m_success/瓊草", 0, member[i]);
        }
        
        message_vision( HIG "$N在虛空中輕輕釦動幾下，一陣優美的樂聲中，$N被送到了一個奇異的地方！\n" NOR, this_player());
        message("channel:chat", HBMAG"【精靈神界】精靈之門開啟，某小隊進入了精靈神界，破解神龍的封印!\n"NOR, users());
        return 1;
}
