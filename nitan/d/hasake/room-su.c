// room-su1.c 

inherit ROOM;
string look_sign(object me);

void create()
{
        set("short", "蘇魯克的家");
        set("long", @LONG
由於蘇魯克的妻子十年前被強盜害死，只剩下蘇魯克和他兒子蘇普兩
人，所以屋裏亂七八糟的。但蘇魯克並不在意，因為他覺得象他這樣的草
原漢子是不能去做女人們做的事情的。火堆一旁的大掛毯上掛着兩兩張精
致的羊毛毯子(tanzi)。
LONG
        );
        set("exits", ([
            "northeast" : __DIR__"shuijing",
            "east" : __DIR__"caoyuan7",
            "west" : __DIR__"caoyuan7",
            "south" : __DIR__"caoyuan7",
        ]));

        
set("item_desc", ([
                "tanzi": (: look_sign :),
        ]) );
        set("objects", ([
                    __DIR__"npc/su" : 1,

        ]));

        setup();
//        replace_program(ROOM);
}
string look_sign(object me)
{
        if(me->query_skill("blade",1)<30 ) {
    return "  一張毛毯上織著一個大漢，揮舞長刀，正在和一頭豹子搏鬥，地上還有隻
被砍翻了的豹子，遠處一頭豹子正挾著尾巴逃走。另一張毛毯上織著一個男孩，
刺死了一頭大灰狼。那二人一大一小，都是威風凜凜，英姿颯爽。\n";
        } else {
        set_temp("su_tanzi", 1, me);
        return "  一張毛毯上織著一個大漢，揮舞長刀，正在和一頭豹子搏鬥，地上還有隻
被砍翻了的豹子，遠處一頭豹子正挾著尾巴逃走。另一張毛毯上織著一個男
孩，刺死了一頭大灰狼。那二人一大一小，都是威風凜凜，英姿颯爽。你定
了定神，隱約感覺畫裏似乎隱藏着極為高明的刀法\n";
}
}

void init()
{
        add_action("do_wudao", "liandao");  
}

int do_wudao(string arg)
{
        object me=this_player();
        object weapon=query_temp("weapon", me);

    if( !query_temp("su_tanzi", me)) return 0;

    if( !arg || arg!="tanzi" ) {
                write("你要根據什麼練刀！\n");
                return 1;
        }
        if( !weapon || query("skill_type", weapon) != "blade" )
                return notify_fail("你手中無刀，怎麼練？\n");

        if ((int)me->query_skill("blade", 1) >100 )
        return notify_fail("你已經竭盡全力去體會毯子上暗藏的刀法精要，但是無法再增長你的基本刀法了！\n");
    
        //    me->receive_damage("jingli", 10+random(15));
                me->receive_damage("jing",random(10));
        write("你對照着毯子上暗藏的刀法精義，揮舞長刀，漸漸地悟出了一些有關基本刀法的精要之所在。\n");
         me->improve_skill("blade",query("int", me));
         return 1;
}                                     
int valid_leave(object me, string dir)
{
        set_temp("su_tanzi", 0, me);
       return 1;
         
}
