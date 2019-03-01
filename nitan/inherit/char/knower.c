// inherit object: knower.c
// 消息靈通人士繼承此對象

#include <ansi.h>

inherit NPC;

int is_knower() { return 1; }

// 接收打聽消息
mixed accept_ask(object ob, string topic)
{
        return QUEST_D->generate_information(this_object(), ob, topic);
}
