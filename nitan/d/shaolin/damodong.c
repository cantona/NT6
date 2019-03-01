// Room: /d/shaolin/damodong.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "達摩洞");
        set("long", @LONG
這裡是達摩古洞。五百年前南天竺僧人菩提達摩來到少林寺，見
此風水寶地，就住下來廣羅弟子，傳授禪宗，開創少林寺佛教禪宗千
年不敗之基。達摩祖師常在此面壁悟道，一坐十年，壁間隱隱似仍可
看到他面壁時的打坐姿態。除地上的幾塊竹片外，洞中空無一物。
LONG );
        set("exits", ([
                "out" : __DIR__"bamboo1",
        ]));
        set("objects",([
                "/clone/book/book-bamboo" : 1,
                CLASS_D("shaolin")+"/da-mo" : 1,
        ]));
        setup();
}

void init()
{
        object me = this_player();

        if( query_temp("bamboo/count", me) == 14 && 
            (int)me->query_skill("dodge", 1) >= 30 &&
            (int)me->query_skill("dodge", 1) <= 100 &&
            present("bamboo", me) )
        {
                me->receive_damage("jing", 20);
                me->improve_skill("dodge",query("dex", me));
        }

        add_action("do_mianbi", "面壁");        
        add_action("do_mianbi", "mianbi");        
}

int do_mianbi()
{
        object me = this_player();

        message_vision("$N面對著達摩洞後半邊的石壁跌坐靜思，良久，似有所悟。\n", me);
        
        me->set_busy(10);
        set("shen", 0, me);

        return 1;
}