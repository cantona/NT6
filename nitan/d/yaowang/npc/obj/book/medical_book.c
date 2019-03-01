inherit ITEM;

void create()
{
       set_name("醫藥知識", ({ "medicine book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
        set("unit", "本");
        set("long",
"這本書上面只有一些字跡模糊的字句，似乎\n"
"寫的是一些配藥解毒的基本法門。\n");
        set("value", 800);
        set("material", "paper");
        set("skill", ([
        "name":         "medical", // 武功名稱,

        "exp_required": 5000,    // 讀此書需要的最低經驗.
        "jing_cost":     10,      // 讀書花的神.
        "difficulty":   20,      // 參看 /cmds/std/study.c
        "max_skill":    40,      // 能讀到的最高等級.
]) );
        }
}
int is_yaowang_book() { return 1; }

