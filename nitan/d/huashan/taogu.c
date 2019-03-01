// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void reset();
int valid_leave(object, string);

void create()
{
        set("short", "桃谷");
        set("long", @LONG
小徑盡頭盡是一山谷，氣候適中，四季如春。山谷內長滿了一大
片桃林，真是一處好所在。遺罕的是此處竟然喧鬧之極，便如身處酒
肆之中，原來有幾個老兒在為一件芝麻綠豆的小事高聲爭論不休。東
北方還有一條小徑。
LONG );

        set("exits", ([
                "south" : __DIR__"xiaojing1",
                "northeast" : __DIR__"xiaojing2",
        ]));

        set("objects", ([
                __DIR__"npc/tao6" : 1,
                __DIR__"npc/tao5" : 1,
                __DIR__"npc/tao4" : 1,
                __DIR__"npc/tao3" : 1,
                __DIR__"npc/tao2" : 1,
                __DIR__"npc/tao1" : 1,
        ]));

        set("no_clean_up", 0);

        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_hit", "hit");
}

int do_hit(string arg)
{
        write("明人不作暗事，還是光明正大地挑戰吧！\n");
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query("family/master_id", me) != "feng qingyang" && dir == "northeast"){

        if( !query_temp("win/tao1", me) && present("tao genxian",environment(me)) )
                return notify_fail("桃根仙伸手一攔道：你還沒跟我較量呢！\n");

        if( !query_temp("win/tao2", me) && present("tao ganxian",environment(me)) )
                return notify_fail("桃幹仙側身攔路道：你還沒跟我比劃喲！\n");

        if( !query_temp("win/tao3", me) && present("tao zhixian",environment(me)) )
                return notify_fail("桃枝仙閃身攔道說：你怎麼把我給忘了呀！\n");

        if( !query_temp("win/tao4", me) && present("tao yexian",environment(me)) )
                return notify_fail("桃葉仙雙手一攤說：你想到那兒去呀？！\n");

        if( !query_temp("win/tao5", me) && present("tao huaxian",environment(me)) )
                return notify_fail("桃花仙笑嘻嘻地說：該輪到我來陪你過兩招了吧！\n");

        if( !query_temp("win/tao6", me) && present("tao shixian",environment(me)) )
                return notify_fail("桃實仙強壯膽色說：打得過我便讓你去見風前輩！\n");

    }           

    return ::valid_leave(me, dir);
}
