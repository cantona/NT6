// mask.c
//

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "面具" NOR, ({ "mian ju", "mask" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("super_mask", 1);
                set("long", "這似乎是一個由人皮制成的面具。\n");
                set("value", 10000);
        }
        set("auto_load", 1);
        setup();
}

void init()
{
        add_action("do_pretend", "pretend");
}

int do_pretend(string arg)
{
        object who;
        object me;
        string *mask;
        string pshort;

        if (! arg)
                return notify_fail("你想假裝誰？\n");

        me = this_player();
        if (arg == "none" || arg == "cancel")
        {
                if (! query_temp("owner"))
                        return notify_fail("你現在並沒有使用面具。\n");

                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                message_vision("$N從臉上取下了一個人皮面具。\n", me);
                return 1;
        }

        if (me->query_skill("pretending", 1) < 100)
                return notify_fail("你拿著面具摸來摸去，就是不會使用。\n");

        if( query("age", me) >= 60 && 
            !query("special_skill/youth", me) )
                return notify_fail("你太老了，難以扮得像。\n");

        if (me->query_condition("killer"))
                return notify_fail("通緝犯無法戴面具。\n");

        if( sscanf(base_name(environment(me)), "/maze/battle%*s") )
                return notify_fail("戰場裡無法戴面具。\n");

        if (! objectp(who = present(arg, environment(me))) || 
            ! living(who))
                return notify_fail("你想假裝誰？\n");

        if (wizardp(who))
                return notify_fail("你無法假扮巫師。\n");

        if( !query("can_speak", who) )
                return notify_fail("假扮" + who->name() + "？好像太難了點。\n");

        // 因為呼叫short()有時候會表述對方的狀態，所以不直接
        // 拷貝who->short()，而是直接看復制對方的應用short()，
        // 如果沒有就復制對方的真實short()。
        if( sizeof(mask=query_temp("apply/short", who)) )
                pshort = mask[sizeof(mask) - 1];
        else
                pshort = who->short(1);

        write("你開始假裝" + who->name() + "。\n");
        set_temp("apply/name", ({who->name()}), me);
        set_temp("apply/id", who->parse_command_id_list(), me);
        set_temp("apply/short", ({pshort}), me);
        set_temp("apply/long", ({who->long()}), me);
        set_temp("owner", me);
        return 1;
}

int move(mixed dest)
{
        object me;

        if (me = query_temp("owner"))
        {
                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                delete_temp("owner");
        }

        return ::move(dest);
}
void remove(string euid) 
{
        object me;

        if (me = query_temp("owner"))
        {
                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                delete_temp("owner");
        }
        ::remove(euid);
}
