#include <ansi.h> 

inherit ROOM;

void create()
{
        set("short", WHT "石室" NOR);
        set("long", @LONG
這是一間在山腹中鑿成的小石屋，中間有一座石桌 (shizhuo)，桌上擺
放著一盞油燈，散發出暗淡昏黃的光亮。屋內光線很暗，四周還散發著一股
腐爛霉臭的味道。
LONG );

        set("exits", ([
                "eastup" : __DIR__"shijie-3",
        ]));

        set("item_desc",([
                "shizhuo": WHT "\n一座石桌，桌身好象是和石屋連在一起的，上面重重的印著兩個手印。\n " NOR,
                "shouyin": WHT "\n一雙在石桌上的手印，你可以試著把雙手嵌(qian)進去。\n " NOR,
        ]));

        set("mishi_book", 1);
        setup();
}

void init()
{
        add_action("do_qian", "qian");
}

int do_qian(string arg)
{
        object me, ob;
        me = this_player();

        if ( ! arg || arg != "shouyin")
                return notify_fail("你要幹什麼？\n");

        if ((int)me->query_skill("tie-zhang", 1) < 50 )
        {
                message_vision(HIY "$N" HIY "將雙手嵌在石桌的手印上，結果什麼都沒有發生。\n" NOR, me);
                return 1; 
        }

        if( query("mishi_book") == 1 )
        {
                message_vision(HIR "$N" HIR "將雙手嵌在石桌的手印上，只聽「轟隆隆」一陣悶響，石桌下豁"
                               "然有一本書籍。\n" NOR + HIC "$N" HIC "見狀大喜，立忙將其揀了起來。\n"
                               NOR, me);
                addn("mishi_book", -1);
                ob = new(__DIR__"obj/zhangpu");
                ob->move(me);
        } else
                return notify_fail(HIR "\n你將雙手嵌在石桌的手印上，只聽「轟隆隆」一陣悶響，石桌"
                                   "移開，可是下面什麼也沒有。\n" NOR);

        return 1;
}