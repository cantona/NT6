#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ss_poison"; }

string chinese_name() { return "生死符"; }

string update_msg_others()
{
       return HIR "只見$N" HIR "哀嚎連連，雙手在身上一陣亂抓，苦不堪言。\n" NOR;
}

string update_msg_self()
{
        return HIB "忽然一股寒流夾著一陣灼熱湧上心來，你中的生死符發作了！\n" NOR;
}
