// anqi.c 暗器

#include <ansi.h>
#include <combat.h>
inherit ITEM;

#define tired_damage 20

int * max_damage = ({
        400,
        380,
        410,
        410,
        450,
        390,
});

int * fix_damage = ({
        20,
        20,
        20,
        20,
        25,
        22,
});

string * name_str = ({
        "穿雲刺",
        "刺蒺藜",
        "飛燕梭",
        "蜂尾針",
        "梨花釘",
        "袖箭",
});

string * id = ({
        "chuanyun ci",
        "ci jili",
        "feiyan suo",
        "fengwei zhen",
        "lihua ding",
        "xiu jian",
});

string * short_id = ({
        "cc",
        "cj",
        "fs",
        "fz",
        "ld",
        "xj",
});

string * des_str = ({
        "這是一柄穿雲刺，柄上系著一根細鏈，可以用于飛刺作暗器。\n",
        "這是一顆渾身都是倒刺的鐵蒺藜，可以當作暗器使用。\n",
        "這是一條形似燕子的梭鏢。\n",
        "這東西似乎是兒童玩耍的小弓一樣，用青銅合金打造的弓柄，蛟筋做成的弓弦好象很結實。\n",
        "一個精致的白銀打造的小盒子，正面好象有很多細若發絲的孔。\n頂部做著一個機鈕，旁邊用小纂刻著‘暗器之王’幾個字。\n",
        "這是一柄袖箭，設計得極其精巧，可以裝在袖筒裡用以暗算別人。\n旁邊有一個小機鈕，一按機鈕，袖箭就會發射(shot)出去了。\n",
});

string * shot_str = ({
        "$N一抖手中的鐵鏈，穿雲刺脫手向$n刺過去！\n",
        "$N從懷內摸出一雙鐵手套戴好，從身邊摸出一顆刺蒺藜，擲向$n！\n",
        "$N手一翻，掌心暗藏的飛燕梭直射$n！\n",
        "$N拉開小弓的弓弦，搭上一支蜂尾針，向$n射去！\n",
        "$N將釘盒上的機鈕一掀，只聽得‘嗤嗤’破空聲不斷，數十細若發絲的梨花釘一
掠而過，直射$n！\n",
        "$N抬起手來按動了機鈕，一支暗器從$N的袖筒裡向$n射去！\n",
});

string * target_str = ({
        "結果$N一驚之下，沒有躲開這一擊！\n",
        "結果$N一驚之下，沒有躲開這一擊！\n",
        "$N慘叫一聲，被射個正著！\n",
        "$N還沒來得及避開，就被射中了！\n",
        "$N只覺得眼前白茫茫一片，避無可避，被暗器射個正著！\n",
        "只聽$N慘叫一聲，被暗器射個正著！\n",
});

string * escape_str = ({
        "結果中途似乎被什麼東西碰了一下，暗器失去了準頭，沒有傷到$N。\n",
        "結果$N輕巧地往旁邊一讓，暗器落了空。\n",
        "結果$N一閃，暗器沒有射中。\n",
        "$N側身一讓，暗器擦著$N的手臂掠過，僅僅是劃破了$N的皮肉。\n",
        "結果$N一縮身，所有暗器都落了空。\n",
        "$N本能地往旁邊一讓，袖箭只是擦破了$N的皮肉，並沒有造成多大傷害。\n",
});

int i; 
void init()
{
        add_action("do_shot","shot");
}

void create()
{
        i = random(sizeof(name_str));

        set_name(HIY+name_str[i]+NOR, ({ id[i],short_id[i] }) );
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "盒");
                set("value", 0);
                set("material", "steel");
                set("long", des_str[i]);
        }
        setup();
}

int do_shot(string arg)
{
        object obj,weapon;
        object me = this_player();
        int lv1,lv2,lv3,lv4,damage;
        string skill_type;
        int tired;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡禁止戰鬥。\n");
        if( !arg)
                return notify_fail("你要射擊誰？\n");
        if( !objectp(obj = present(arg, environment(me)) ))
                return notify_fail("這裡沒有這個人！\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");
        if (obj == me) return notify_fail("射自己？別想不開啊。\n");

        message_vision(HIR+shot_str[i]+NOR,me, obj);

        if( objectp(weapon=query_temp("weapon", obj)) )
                skill_type=query("skill_type", weapon);
        else skill_type = "unarmed";

        lv1 = COMBAT_D->skill_power(obj, skill_type, SKILL_USAGE_DEFENSE);
        lv2 = COMBAT_D->skill_power(obj, "dodge", SKILL_USAGE_DEFENSE);

        lv3 = (lv2 + (weapon? lv1: (lv1/10))) / 100 + 1;
        lv4=query_temp("apply/armor", obj);

        tired=query("total_tired", obj);
        damage = random(max_damage[i]) - random(lv3+lv4) + fix_damage[i] + random(tired_damage * tired);

        if (damage > 0 )
        {
                obj->receive_wound("qi",damage);
                message_vision(HIR+target_str[random(sizeof(target_str))]+NOR,obj);
        }
        else message_vision(HIW+escape_str[random(sizeof(escape_str))]+NOR,obj);

        destruct(this_object());
        return 1;
}
