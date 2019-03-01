// qinpu.c
inherit ITEM;

void create()
{
        set_name("黃石譜", ({ "huangshi pu" ,"pu" ,"book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本琴譜，你讀着讀着，似
乎可以從裏面發現一些其他的東西。\n"
                        "原來這是一本藏着劍法的琴譜。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name": "wuyun-jian",        // name of the skill
                        "exp_required": 100, 
                        "jing_cost": 10,
                        "difficulty": 20,          // the base int to learn this skill
                        "max_skill": 80
                ]) );
        }
}
