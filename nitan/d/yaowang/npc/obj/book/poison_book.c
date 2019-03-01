inherit ITEM;

void create()
{
       set_name("毒經總決", ({ "tang-du book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
        set("unit", "本");
        set("long",
"這本書上面只有一些字跡模糊的字句，似乎\n"
"寫的是一些用毒的基本法門。\n");
        set("value", 800);
        set("material", "paper");
        set("skill", ([
        "name":         "poison", // 武功名稱,

        "exp_required": 1000,    // 讀此書需要的最低經驗.
        "jing_cost":     15,      // 讀書花的神.
        "difficulty":   20,      // 參看 /cmds/std/study.c
        "max_skill":    50,      // 能讀到的最高等級.
]) );
        }
}
int is_yaowang_book() { return 1; }

