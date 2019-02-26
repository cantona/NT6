// yebee.c 玉蜂

inherit NPC;
#include <ansi.h>;
void create()
{
        set_name(HIY"玉蜂"NOR, ({ "yu bee", "bee" }) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        seteuid(getuid());
        set("age", 1);
        set("long", "這是一羣玉色的蜜蜂，個頭比普通蜜蜂大得多，\n");
        set("attitude", "peaceful");
        set("no_train", 1);
        set("combat_exp", 500);
        set("chat_chance", 3);
        set("chat_msg", ({
                "玉蜂嚶嚶嗡嗡地亂舞個不停。\n",
                "玉蜂飛速地向你衝過來，好像要叮你一口。可是在要觸及你的一剎那又飛開了。\n",
                "玉蜂嗡嗡嗡飛過來，在你頭上轉了一圈，又飛走了。\n",
        }) );
        set_temp("apply/attack", 200);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 2);
        set_temp("apply/armor", 1);
        setup();
}
void init()
{
        ::init();
        if(strsrch(file_name(environment(this_object())),"baihuagu") < 0)
        {
                write("玉蜂嗡嗡嗡轉了一圈，飛回百花谷去了。\n");
                destruct(this_object());
        }
}
