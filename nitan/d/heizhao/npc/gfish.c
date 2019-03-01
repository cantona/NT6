// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit NPC;

void create()
{
        set_name("金娃娃", ({ "jin wawa", "jin", "fish" }) );
        set("race", "野獸");
        set("age",35);
        set("long", "此物似魚非魚，似蛇非蛇，全身金色，有尺來長。\n");

        set("attitude", "peaceful");
        
        set("str", 20);
        set("combat_exp", 85000);
        
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 120);
        set_temp("apply/damage", 2);
        set_temp("apply/armor", 1);

        setup();
}















