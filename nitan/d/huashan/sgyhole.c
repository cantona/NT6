// Room: /d/huashan/sgyhole.c

inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
這是一個毫不起眼的山洞，但是裏面的石壁上卻畫滿了五嶽劍派
所有已經失傳的精妙絕招。花崗巖石壁(wall)上很多小人，全是用利
器刻制，想見當初運力之人內力十分深厚。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "southup"   : __DIR__"zhandao",
            "northdown" : __DIR__"sgyhole2",
            "out"       : __DIR__"sgyhole1",
        ]));
        set("item_desc", ([ 
            "wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L
TEXT
        ]));

        setup();
}
void init()
{
        add_action("do_mianbi", "mianbi");
}

int do_mianbi()
{
        object ob;
        int c_skill;

        ob = this_player();

        if (ob->is_busy()) return notify_fail("你正忙着呢！\n");
        c_skill = (int)ob->query_skill("sword", 1);
        if (c_skill < 20)
        {
                message_vision("$N對劍法的瞭解顯然太低，無"
                               "法領悟石壁內容。\n", ob);
                return 1; 
        }

        if (! ob->can_improve_skill("sword"))
        {
                message_vision("$N的實戰經驗不足，無法領悟"
                               "石壁內容。\n", ob);
                return 1; 
        }

        if( query("jing", ob)<20 )
        {
                message_vision("$N太累了，現在無法領悟石壁內容。\n",ob);
                return 1; 
        }

        if (c_skill >= 100)
        {
                message_vision("$N覺得石壁內容太膚淺了。\n", ob);
                return 1;
        }

        message_vision("$N面對着石壁趺坐靜思，良久，對基本"
                       "劍法似有所悟。\n", ob);
        ob->improve_skill("sword",1+random(query("int", ob)));
        ob->receive_damage("jing", 15);
        ob->start_busy(random(1));
        return 1;
}