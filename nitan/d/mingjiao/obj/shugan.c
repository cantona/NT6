// Code of JHSH
// shugan.c 樹幹
// zhangchi 7/00


inherit ITEM;

void create()
{
        set_name("樹幹", ({ "shu gan","trunk"}) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一根剛剛砍下來的樹幹。\n");
                set("unit", "根");
                set("no_get", "這麼大的樹幹，你能拿起來嗎？");
                set("value",1);
        }
}

void init()
{
        add_action("do_give","give");
        add_action("do_carry","carry");
        add_action("do_carry","kang");
        if (wizardp(this_player()))
                add_action("set_owner","setowner");
}

int set_owner(string arg)
{
        if (!arg) return notify_fail("指令格式：setowner <xxx>\n");
        set("owner",arg);
        write("OK!\n");
                
        return 1;
}

int do_give()
{
        return notify_fail("你正扛着大木頭呢，怎麼給人？\n");
}

int do_carry(string arg)
{
        object owner;
        object me=this_player();

        if (!arg) return 0;

        if (me->is_busy() || me->is_fighting() )
                return notify_fail("你正忙着呢。\n");

        if (arg != "shu gan" && arg != "trunk")
                return notify_fail("你要扛什麼？\n");

        if( query("owner") != query("id", me) )
                if (present(query("owner"),environment(me)) )
                {
                        owner=find_player(query("owner"));
                        message_vision("$N偷偷地想把樹幹抬起來，突然$n瞪了$N一眼，嚇地$N趕緊縮手。\n",me,owner);
                        return 1;
                }
                else
                {
                        message_vision("$N瞧了瞧旁邊沒人，偷偷摸摸地把樹幹扛到肩上。\n",me);
                        this_object()->move(me);
                        set_temp("apply/short", ({(query("title", me)+""+query("name", me)+"扛着一根樹幹")}), me);

                        return 1;
                }
        
        message_vision("$N使勁一抬，將剛砍下來的樹幹扛到肩上\n",me);
        this_object()->move(me);
        set_temp("apply/short", ({(query("title", me)+""+query("name", me)+"扛着一根樹幹")}), me);


        return 1;
}