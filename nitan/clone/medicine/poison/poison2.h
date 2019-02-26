// poison2.h
// Last Modified by winder on Feb. 28 2001

int do_tu(string arg)
{
        string what, my;
        object ob, me = this_player();
        int i;
        i = (me->query_skill("poison")/10)+3+(me->query_skill("five-poison")/10)+3;

        if( !arg || sscanf(arg, "%s on %s", my, what)!=2 || !id(my) )
                return notify_fail("命令格式: tu <藥> on <武器>。\n");

        ob = present(what, me);
        if( !ob ) return notify_fail("你身上沒有" + what + "這樣東西。\n");
        if( !query("weapon_prop", ob) )
                return notify_fail("只能塗在武器上。\n");
        
        set("poisoned", query("pour_type"), ob);
        set("poison_number",query("poison_number",  ob)+i, ob);

        set_temp("apply/long", ({query("long", ob)+"但看上去"+query("drug_color")+"，好像是被餵了劇毒。\n"}), ob);
        message_vision("$N背過身去，將"+query("name")+"塗在$n上。\n", me, ob);
        me->start_busy(2);
        add_amount(-1);
        return 1;
}

void destruct(object ob)
{
        message_vision("$N慢慢地燃燒完了。\n",ob);
        ob->add_amount(-1);
        return;
}
