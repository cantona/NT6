// buwei3.c

inherit ROOM;

void create()
{
        set("short", "偏廳");
        set("long", @LONG
偏廳裡供奉著華山歷代祖師的神位。正中神案的牆上是華山派開
山祖師風祖師的畫象。畫象神情清雋，非常傳神。神案上香爐裡插著
三柱清香，香煙裊裊上升，散發著一股檀香味。西面有扇門通往外面
的正廳。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"buwei1",
        ]));
        set("no_clean_up", 0);
        set("valid_startroom","1");
        set("objects", ([ /* sizeof() == 2 */
                CLASS_D("huashan")+"/first": 1,
        ]));

        set("item_desc", ([
                      "picture" : "一個神情清雋的中年書生，腰間配著一把長劍。\n",
                "畫象" : "一個神情清雋的中年書生，腰間配著一把長劍。\n",
        ]));

        set("paper_count", 1);

        setup();
        "/clone/board/huashan_b"->foo();
        //replace_program(ROOM);
}

/*
void init()
{
        add_action("do_ketou","ketou");
           add_action("do_ketou","kneel");
}
*/

int do_ketou(string arg)
{
           object paper, me = this_player();
        int level1, level2, level3;

        message_vision("$N恭恭敬敬地在神案前的團蒲上跪了下來，對著神位磕了三個響頭。\n", me);
        me->receive_damage("qi", 5, "力盡氣絕而死");
        me->start_busy(1);

        if( query("qi", me) <= 50 )
                write("你只覺得腦子有些昏昏沉沉的。\n");
        if( query("qi", me) <= 20 )
                write("你覺得天旋地轉，似乎馬上便要暈去。\n");

        if( !(query("family/family_name", me) == "華山派"))return 1;

        if( !query("huashan/yin-jue", me) && query("huashan/yinjue", me)<500){
                addn("huashan/yinjue", 1, me);
                return 1;
        }

        level1 = me->query_skill("ziyin-yin", 1);
        level2 = me->query_skill("zhengqi-jue", 1);
        level3 = me->query_skill("zixia-gong", 1);

        if( level1 >= 120 && level2 >= 120 && level3 >= 150 && !query("huashan/yin-jue", me)){
                paper=new(__DIR__"obj/zixia_paper");
                if ( !paper ) return 1;

                paper->move(me);
                addn("paper_count", -1);
                set("huashan/yin-jue", 1, me);
                delete("huashan/yinjue", me);

                write("你在團蒲上重重地一磕，團蒲的邊上忽然裂了開來，露出一小段紙箋。\n");
                write("你仔細的將紙箋抽出一看，上面密密麻麻的記載了練功心法，似乎與紫霞\n");
                write("功一脈相承，但卻更加深奧。\n");
                write("你細讀良久，突然晃然大悟，原來這便是紫霞密笈失傳多時的最後一頁！\n");
                write("你連忙密笈收好。\n");
        }

        return 1;
}
