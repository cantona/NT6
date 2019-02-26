// This program is a part of NT MudLIB
// enchant
// Written by Lonely@nitan.org

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        string what, tessera;
        object item, obj;
        object scroll;
        int flag = 0;

        if( !arg || sscanf(arg,"%s from %s", tessera, what) != 2 )
                return notify_fail("指令格式：enchant <物品> from <裝備>\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if( me->is_fighting() )
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if( !objectp(obj = present(tessera, me)) )
                return notify_fail("你身上沒有 " + tessera + " 這種物品啊。\n");

        if( !objectp(item = present(what, me)) )
                return notify_fail("你身上沒有" + what + "這樣裝備啊。\n");

        if( me->query_skill("enchanting", 1) < 200 )
                return notify_fail("你覺得你的附魔技藝還不夠嫻熟，不敢貿然動手。\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("你現在的精力修為有限，無法附魔物品。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你現在精力不濟，無法附魔物品。\n");

        if( query("equipped", item) )
                return notify_fail("你先卸除他先。\n");

        if( query("no_identify", item) )
                return notify_fail("此物品還沒有簽定。\n");

        if( !query("enchase", item) || !query("enchase/apply_prop", item) )
                return notify_fail("這個物品上面沒有可用作附魔的屬性。\n");

        if( item->is_item_make() || !query("insert", item) )
                return notify_fail("這個物品無法用來附魔的屬性。\n");

        if( query("maze_item", item) )
                return notify_fail("這個物品來歷不明，不可以用作附魔屬性。\n");

        if( query("enchase/increase", item) )
                return notify_fail("改造過的裝備不可以用作附魔屬性。\n");

        if( !query("can_enchant", obj) )
                return notify_fail("只有日魂和月魄才可以用來附魔裝備屬性。\n");

        if( query("enchase", obj) )
                return notify_fail(obj->name()+"上已經附魔過屬性了。\n");

        if( query("skill_type", item )
         || (query("armor_type", item) == "hands"
         || query("armor_type", item) == "finger") )
        {
                if( query("can_enchant", obj) != "weapon" )
                        return notify_fail("只有日魂才可以用來附魔此裝備屬性。\n");
        }
        else
        {
                if( query("can_enchant", obj) != "armor" )
                        return notify_fail("只有月魄才可以用來附魔此裝備屬性。\n");
        }

        scroll = present("enchant scroll", me);

        if( objectp(scroll) )
                tell_object(me, HIW "\n你雙目微閉，將"+item->name()+HIW"和"+obj->name()+HIW"置於附魔卷軸上凝於身前，運轉內勁迫"
                        "使它們空中旋轉交融。\n" NOR);
        else
                tell_object(me, HIW "\n你雙目微閉，將"+item->name()+HIW"和"+obj->name()+HIW"凝於身前，運轉內勁迫"
                        "使它們空中旋轉交融。\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);

        flag = obj->do_extract(item);

        if( flag ) {
                message("vision", HIW "\n霎時間只見" + me->name() + HIW "身前一道"
                        "光華閃過，但轉瞬即逝，似乎發生了什麼不同尋常的"
                        "事情。\n\n" NOR, environment(me), ({me}));

                tell_object(me, HIW "霎時間只見萬道光華疾閃而過，你急忙伸出雙手將"+obj->name()+HIW"接住，"
                        "發現掌心"+obj->name()+HIW"藴漾着七色霞光。\n\n" NOR);

                if( objectp(scroll) )
                {
                        tell_object(me, HIW"只見"+scroll->name()+HIW"在內力注入下已化為灰燼。\n"NOR);
                        destruct(scroll);
                }
                
                addn("max_jingli", -1, me);

                return 1;
        }
        if( objectp(scroll) )
        {
                tell_object(me, HIW"但見"+scroll->name()+HIW"在內力注入下已化為灰燼。\n"NOR);
                destruct(scroll);
        }
        else
        {
                tell_object(me, HIW"但見"+item->name()+HIW"瞬間破裂，變成片片碎片灑落一地。\n");
                destruct(item);
        }

        tell_object(me, HIR "你不禁一聲長歎。\n" NOR);

        return 1;
}
