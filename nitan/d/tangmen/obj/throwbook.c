// throwbook.c

inherit ITEM;

void create()
{
        set_name("唐門暗器總訣", ({ "book", "shu"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "唐門暗器總訣\n"
                        "這是一本唐門歷代暗器名家總結出來的暗器總訣。\n");
                set("value", 500);
                set("material", "silk");
                set("skill", ([
                        "name":        "throwing",        // name of the skill
                        "exp_required":        100000,        // minimum combat experience required
                        "jing_cost":        10,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        200        // the maximum level you can learn
                ]) );
        }
}
