// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// resolve

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        object item, ob;
        object scroll;
        mapping ins;
        int    i, j;
        string *ks, *ap;
        string my_id, my_name;
        mapping apply;
        mapping data;

        if( !arg )
                return notify_fail("指令格式：resolve <動態裝備>\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if( me->is_fighting() )
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if( !objectp(item = present(arg, me)) )
                return notify_fail("你身上沒有" + arg + "這樣裝備啊。\n");

        if( !objectp(scroll = present("resolve scroll", me)) )
                return notify_fail("你身上沒有分解卷軸。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你現在的內力修為有限，無法分解物品。\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("你現在的精力修為有限，無法分解物品。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你現在精力不濟，無法分解物品。\n");

        if( query("equipped", item) )
                return notify_fail("你先卸除他先。\n");

        if( query("no_identify", item) )
                return notify_fail("此物品還沒有簽定。\n");

        if( !query("enchase", item) || !query("enchase/apply_prop", item) )
                return notify_fail("這個物品上面沒有可用來分解的屬性元素。\n");

        if( item->is_item_make() || !sizeof(ins=query("insert", item)) )
                return notify_fail("這個物品無法用來分解屬性元素。\n");

        if( query("maze_item", item) )
                return notify_fail("這個物品來歷不明，不可以用來分解。\n");

        if( query("enchase/increase", item) )
                return notify_fail("改造過的裝備不可以用來分解屬性元素。\n");

        tell_object(me, HIM "\n你雙目微閉，將分解卷軸與"+item->name()+HIM"凝于身前，運轉內勁迫"
                        "使它們空中旋轉交融。\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);
        
        ap = keys(ins);
        for( i=0; i<sizeof(ap); i++ ) {
                apply = copy(ins[ap[i]]["apply_prop"]);
                ks = keys(apply);
                for( j=0; j<sizeof(ks); j++ ) {
                        my_id = ks[j];
                        my_name = EQUIPMENT_D->chinese(my_id)+"元素";
                        data = ([]);
                        data["element"] = my_id;
                        data["name"] = my_name;
                        ob = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data);
                        ob->set_name(my_name, ({my_id, "element"}));
                        ob->move(me, 1);
                }
        }

        message("vision", HIW "\n霎時間只見" + me->name() + HIW "身前一道道"
                "光華閃過，但轉瞬即逝，似乎發生了什麼不同尋常的"
                "事情。\n\n" NOR, environment(me), ({me}));

        tell_object(me, HIW "霎時間只見萬道光華疾閃而過，你急忙伸出雙手，發現掌心蘊漾著七色霞光。\n\n" NOR);

        addn("max_jingli", -1, me);
        destruct(scroll);
        destruct(item);

        return 1;
}

