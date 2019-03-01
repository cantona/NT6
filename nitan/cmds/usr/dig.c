// dig.c
// Find.

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env, *inv;

        if(!me || !objectp(env = environment(me)))
                return 0;

        if(!function_exists("cmd_dig_function", env))
                return notify_fail("你四處看了看，發現這裡沒什麼可以挖掘的地方。\n");

        if(!sizeof( inv = filter_array(all_inventory(me),
                (: $1->is_mine_tool() && $1->tool_can_use() :)) ) )
                return notify_fail("你身上沒有用于挖掘的工具。\n");

        inv[0]->use_this_tool();

        notify_fail("你四處挖了挖，什麼也沒有挖出來。\n");
        return env->cmd_dig_function(me, arg);
}

