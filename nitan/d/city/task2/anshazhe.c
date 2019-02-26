// anshazhe.c 暗殺者
inherit NPC;
#include "aninit.h"

void create()
{
        string weapon;
        int i;

        i = random(sizeof(name_msg));
        set_name(name_msg[i], ({ long_id[i], short_id[i] }) );
        set("gender", sex_msg[i] );
        set("age", 15 + random(40) );
        set("long","一個普通的人，放在人羣中沒有一點突出之處。\n");

        weapon = weapon_msg[random(sizeof(weapon_msg))];
        setup();
        carry_object(weapon);
        carry_object("/clone/misc/cloth")->wear();
}
