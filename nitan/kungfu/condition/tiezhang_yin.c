#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "tiezhang_yin"; }

string chinese_name() { return "鐵掌陰寒勁"; }

string update_msg_others()
{
        return HIB "$N" HIB "面色慘白，嘴皮烏紫，冷不丁打了一個寒戰。\n" NOR;
}

string update_msg_self()
{
        return HIB "你感到胸口處傳來陣陣刺痛，全身血液竟似要凝結住一般。\n" NOR;
}

