// fenyi.c

inherit NPC;

#include <ansi.h>
#include "bajiao.h"

void create()
{
        set_name(HIM "粉衣" NOR, ({ "fen yi", "fen", "yi" }) );
        set("title", CYN "羣玉八嬌" NOR);
        set("gender", "女性" );
        set("age", 22);
        set("str", 30);
        set("per", 40);
        set("long", @LONG
一個全身上下穿着粉裝，領露酥胸的美女．
LONG);
        set("combat_exp", 10);
        set("attitude", "friendly");

        setup();
        carry_object("/d/changan/npc/obj/skirt")->wear();
}