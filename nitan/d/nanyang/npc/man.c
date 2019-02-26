// Room: /d/nanyang/npc/man.c
// Last Modified by winder on Nov. 20 2001

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("大漢", ({ "da han","man" }) );
        set("title","");
        set("long","一位彪形大漢。\n");
        set("age", 20+random(20));
        set("gender", "男性");
        seteuid(getuid());
        set_skill("unarmed",60);
        set_skill("blade",50);
        set("combat_exp", 1000);
        set("talk_msg",({
                "這裏是南陽城",
                "這裏是諸葛亮的故鄉",
                "柯府老爺為民除害，大家都感恩待德呀！",
                "南陽城北接中原，南渡漢水。",
        }));
        setup();
        carry_object(WEAPON_DIR"blade")->wield();
        carry_object(CLOTH_DIR"cloth")->wear();
}