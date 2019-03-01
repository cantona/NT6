#include <ansi.h>
#include <armor.h>

inherit FINGER;
inherit F_GEMS;

void init_sockets(object me)
{
        set("max_sockets", 1);
        if (me->query("combat_exp") > 10000000)
                add("max_sockets", 1);
        if ((int)query("sockets/max")>3)
        set("sockets/max",3);
        if (me->query("combat_exp") > 10000000)
                add("max_sockets", 1);
        if (me->query("diablo/" + TYPE_FINGER + "/id") != query("id")) return;
set("usr_id",me->query("id"));

        set("sockets", me->query("diablo/" + TYPE_FINGER + "/sockets"));
        set_ring_desc();
}

void setup()
{
        init_sockets(this_player());
        ::setup();
}

void spec_prop(object me, string socket, int socket_level, int mode)
{
        if (!valid_gem(socket, socket_level)) return;
if (me->query("diablo/" + TYPE_FINGER + "/id") != query("id")) return;
if (me->query("id")!=query("usr_id")) return;
        switch (socket) {
        case "ruby":
                if (mode == 1)
                        message_vision(HIR + query("name") + HIR"射出一道耀眼的紅光，$N在神光的沐浴下感到體力異常的充沛！\n"NOR, me);
                else
                        message_vision(HIR"隨著神光漸漸的隱去，$N的體力又恢復正常了。\n"NOR, me);
                me->add("max_qi", me->query("max_neili") * socket_level * mode / 10);
                me->add("eff_qi", me->query("max_neili") * socket_level * mode / 10);
                me->add("qi", me->query("max_neili") * socket_level * mode / 10);
                break;
        case "topaz":
                if (mode == 1)
                        message_vision(HIY + query("name") + HIY"射出一道奪目的黃光，$N在神光的沐浴下感到精力異常的充沛！\n"NOR, me);
                else
                        message_vision(HIY"隨著神光漸漸的隱去，$N的精力又恢復正常了。\n"NOR, me);
                me->add("max_jing", me->query("max_neili") * socket_level * mode / 30);
                me->add("eff_jing", me->query("max_neili") * socket_level * mode / 30);
                me->add("jing", me->query("max_neili") * socket_level * mode / 30);
                break;
        case "sapphire":
                if (mode == 1)
                        message_vision(HIB + query("name") + HIB"射出一道柔和的藍光，$N在神光的沐浴下感到內力異常的充沛！\n"NOR, me);
                else
                        message_vision(HIB"隨著神光漸漸的隱去，$N的內力又恢復正常了。\n"NOR, me);
                me->add("neili", me->query("max_neili") * socket_level * mode / 10);
                break;
        case "emerald":
                if (mode == 1)
                        message_vision(HIG"忽然從" + query("name") + HIG"裡幻化出一個身披綠紗的幸運女神圍繞著$N的身邊！\n"NOR, me);
                else
                        message_vision(HIG"綠光一閃，$N的幸運女神就不見了。\n"NOR, me);
                me->add_temp("apply/karey", 10 * socket_level * mode);
                break;
        case "amethyst":
                if (mode == 1)
                        message_vision(MAG"一片紫色雲霧迅速從" + query("name") + MAG"中湧出，轉眼間就已經把$N托了起來！\n"NOR, me);
                else
                        message_vision(MAG"紫色雲霧被風吹散了，$N的身形又顯現了出來。\n"NOR, me);
                me->add_temp("apply/dex", 10 * socket_level * mode);
                break;
        case "diamond":
                if (mode == 1)
                        message_vision(HIW"「嘩」，" + query("name") + HIW"劃出一道閃電直沖天際，$N剎時感到體內充滿了力量！\n"NOR, me);
                else
                        message_vision(HIW"漸漸的$N的神色又恢復了正常。\n"NOR, me);
                me->add_temp("apply/str", 10 * socket_level * mode);
                break;
        case "skull":
                if (mode == 1)
                        message_vision(WHT"$N忽然感到一股奇異的力量圍繞著$P，隱隱之間只覺得充斥著莫明的魔力！\n"NOR, me);
                else
                        message_vision(WHT"$N" + query("name") + WHT"中的咒語漸漸失去了效用！\n"NOR, me);
                me->add_temp("apply/magic", 10 * socket_level * mode);
                break;
        }
        return;
}

int wear()
{
        int i, sockets, ret;
        object me = environment();

        if (!(ret = ::wear())) return 0;


        sockets = query("sockets/max");
        for (i = 1; i <= sockets; i++)
                spec_prop(me, query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)), 1);
        return ret;
}

int unequip()
{
        int i, sockets, ret;
        object me = environment();

        if (!(ret = ::unequip())) return 0;

        sockets = query("sockets/max");
        for (i = 1; i <= sockets; i++)
                spec_prop(me, query(sprintf("sockets/socket%d", i)), query(sprintf("sockets/socket%d_level", i)), -1);
        return ret;
}
