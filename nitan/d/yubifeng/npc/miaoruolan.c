// miaoruolan.c 苗若蘭

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("苗若蘭", ({ "miao ruolan", "ruolan", "miao" }) );
        set("gender", "女性");
        set("age", 17);
        set("long","她是天下第一高手，“打遍天下無敵手”的“金面佛”苗人鳳之女。只是自小家教，不習武功。\n");
        set("attitude", "friendly");
        set("str", 15);
        set("int", 15);
        set("con", 19);
        set("dex", 17);
        set("per", 34);
        set("combat_exp", 2000);

        set("chat_chance", 10);
        set("chat_msg", ({
                "苗若蘭幽幽地道：當年那個可憐的小男孩現在也不知怎麼樣了？\n",
                "苗若蘭皺了皺秀眉：爹爹怎麼還沒上山？\n",
        }) );

        setup();
        carry_object(CLOTH_DIR"diaopi")->wear();
}