// Code of JHSH
inherit ITEM;


void create()
{
        set_name("鐵錘", ({ "tie chui", "chui" }) );
        set_weight(9000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一把大鐵錘，是用來打鐵的工具。\n"
);
                set("unit", "把");
                set("no_get", 1);
                set("no_drop", 1);


        }

}