// mianju.c
// modified by cleansword 1996/2/3

inherit ITEM;

void create()
{
        set_name("面具", ({ "mian ju", "mask" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這似乎是一個由人皮製成的面具。\n");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
        setup();
}

void init()
{
        add_action("do_pretend", "pretend");
}

int do_pretend(string arg)
{
        object who;
        if (!arg)
                return notify_fail("你想假裝誰？\n");
        if (arg == "none" || arg == "cancel") {
                delete_temp("apply/name", this_player());
//                this_player()->delete_temp("apply/id");
                delete_temp("apply/short", this_player());
        set("status", 0, this_object());
                delete_temp("apply/long", this_player());
                message_vision("$N從臉上取下了一個人皮面具。\n", this_player());
                return 1;
        }
        if(!objectp(who = present(arg, environment(this_player()))) || 
                !living(who))
                return notify_fail("你想假裝誰？\n");
        write("你開始假裝" + who->name() + "。\n");
//        message_vision("$N戴上了一個精功製成的人皮面具。\n", this_player());
        set_temp("apply/name", ({who->name()}), this_player());
//        this_player()->set_temp("apply/id", ({who->id()}));
        set_temp("apply/short", ({who->short()}), this_player());
        set("status", 1, this_object());
        set_temp("apply/long", ({who->long()}), this_player());
        return 1;
}