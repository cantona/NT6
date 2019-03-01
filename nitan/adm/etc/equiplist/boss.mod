// 套裝組合列表文件表
// boss.xml
// BOSS專用套裝

#modlist
// 對應的套裝
<M3000>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<mod_parts>
A3000:$CYNGRN$龍神護腕$NOR$
A3001:$CYNGRN$龍神鱗甲$NOR$
A3002:$CYNGRN$龍神之翼$NOR$
A3003:$CYNGRN$龍神束帶$NOR$
A3004:$CYNGRN$龍神之觸$NOR$
A3005:$CYNGRN$龍神脛甲$NOR$
A3006:$CYNGRN$龍神戰甲$NOR$
</mod_parts>
<bas>3</bas>
<num>7</num>
<bas_prop>
add_forget:20
add_busy:10
avoid_forget:20
reduce_busy:20
</bas_prop>
<adv_prop>
avoid_busy:20
add_weak:10
avoid_weak:20
add_damage:20
reduce_damage:20
</adv_prop>
</M3000>

#listend

#eqlist
// 套裝的部件
<A3000>
<type>armor/wrists</type>
<name>$CYNGRN$龍神護腕$NOR$</name>
<id>dragon wrists</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:10
</armor_prop>
<enchase>
apply_prop/armor1:60
apply_prop/str:2
apply_prop/con:2
apply_prop/force:2
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:60
apply_prop/str:2
[/1]
[2]
id:magic stone
name:玄石
apply_prop/con:2
apply_prop/force:2
[/2]
</insert>
</A3000>

<A3001>
<type>armor/armor</type>
<name>$CYNGRN$龍神鱗甲$NOR$</name>
<id>dragon armor</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:200
</armor_prop>
<enchase>
apply_prop/armor1:60
apply_prop/str:2
apply_prop/con:2
apply_prop/force:2
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:60
apply_prop/str:2
[/1]
[2]
id:magic stone
name:玄石
apply_prop/con:2
apply_prop/force:2
[/2]
</insert>
</A3001>

<A3002>
<type>armor/surcoat</type>
<name>$CYNGRN$龍神之翼$NOR$</name>
<id>dragon surcoat</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:10
</armor_prop>
<enchase>
apply_prop/armor1:10
apply_prop/str:2
apply_prop/dex:1
apply_prop/dodge:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:10
apply_prop/str:2
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dex:1
apply_prop/dodge:1
[/2]
</insert>
</A3002>

<A3003>
<type>armor/waist</type>
<name>$CYNGRN$龍神束帶$NOR$</name>
<id>dragon waist</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:10
</armor_prop>
<enchase>
apply_prop/armor1:30
apply_prop/parry:10
apply_prop/str:2
apply_prop/int:2
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:30
apply_prop/parry:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/str:2
apply_prop/int:2
[/2]
</insert>
</A3003>

<A3004>
<type>armor/head</type>
<name>$CYNGRN$龍神之觸$NOR$</name>
<id>dragon head</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:30
</armor_prop>
<enchase>
apply_prop/armor1:60
apply_prop/str:2
apply_prop/int:2
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:60
[/1]
[2]
id:magic stone
name:玄石
apply_prop/str:2
apply_prop/int:2
[/2]
</insert>
</A3004>

<A3005>
<type>armor/boots</type>
<name>$CYNGRN$龍神脛甲$NOR$</name>
<id>dragon boots</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:10
</armor_prop>
<enchase>
apply_prop/armor1:30
apply_prop/dodge:10
apply_prop/str:2
apply_prop/dex:5
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:30
apply_prop/dodge:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/str:2
apply_prop/dex:5
[/2]
</insert>
</A3005>

<A3006>
<type>armor/cloth</type>
<name>$CYNGRN$龍神戰甲$NOR$</name>
<id>dragon cloth</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龍之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>3</quality_level>
<armor_prop>
armor:60
</armor_prop>
<enchase>
apply_prop/armor1:80
apply_prop/force:10
apply_prop/str:2
apply_prop/con:2
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:80
apply_prop/force:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/str:2
apply_prop/con:2
[/2]
</insert>
</A3006>


//注重攻擊、傷害加強
<M3001>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<mod_parts>
A3010:$HBBLU$破壞神戰甲$NOR$
A3011:$HBBLU$破壞神披風$NOR$
A3012:$HBBLU$破壞神腰帶$NOR$
A3013:$HBBLU$破壞神頭盔$NOR$
A3014:$HBBLU$破壞神戰靴$NOR$
A3015:$HBBLU$破壞神護腕$NOR$
A3016:$HBBLU$破壞神戰衣$NOR$
</mod_parts>
<bas>4</bas>
<num>7</num>
<bas_prop>
attack:700
damage1:9000
ap_power:30
da_power:50
</bas_prop>
<adv_prop>
add_forget:50
add_damage:50
add_busy:10
fatal_blow:50
counter_damage:50
</adv_prop>
</M3001>


// 六個配件
<A3010>
<type>armor/armor</type>
<name>$HBBLU$破壞神戰甲$NOR$</name>
<id>diablo armor</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:200
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:80
apply_prop/defense:50
apply_prop/dp_power:2
apply_prop/reduce_busy:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:80
apply_prop/defense:50
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_busy:1
[/2]
</insert>
</A3010>

<A3011>
<type>armor/surcoat</type>
<name>$HBBLU$破壞神披風$NOR$</name>
<id>diablo surcoat</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:30
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:30
apply_prop/defense:10
apply_prop/dp_power:2
apply_prop/reduce_damage:3
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:30
apply_prop/defense:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_damage:3
[/2]
</insert>
</A3011>

<A3012>
<type>armor/waist</type>
<name>$HBBLU$破壞神腰帶$NOR$</name>
<id>diablo waist</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:30
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:30
apply_prop/defense:10
apply_prop/dp_power:2
apply_prop/reduce_damage:3
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:30
apply_prop/defense:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_damage:3
[/2]
</insert>
</A3012>

<A3013>
<type>armor/head</type>
<name>$HBBLU$破壞神頭盔$NOR$</name>
<id>diablo head</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:100
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:50
apply_prop/defense:20
apply_prop/dp_power:2
apply_prop/reduce_damage:3
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:50
apply_prop/defense:20
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_damage:3
[/2]
</insert>
</A3013>

<A3014>
<type>armor/boots</type>
<name>$HBBLU$破壞神戰靴$NOR$</name>
<id>diablo boots</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:30
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:30
apply_prop/defense:10
apply_prop/dp_power:2
apply_prop/reduce_busy:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:30
apply_prop/defense:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_busy:1
[/2]
</insert>
</A3014>

<A3015>
<type>armor/wrists</type>
<name>$HBBLU$破壞神護腕$NOR$</name>
<id>diablo wrists</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:30
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:30
apply_prop/defense:10
apply_prop/dp_power:2
apply_prop/reduce_busy:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:30
apply_prop/defense:10
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_busy:1
[/2]
</insert>
</A3015>

<A3016>
<type>armor/cloth</type>
<name>$HBBLU$破壞神戰衣$NOR$</name>
<id>diablo wrists</id>
<long>此裝備只是瞧上一眼，已經讓人殺意騰騰、血脈噴張、戰意無窮。</long>
<value>300000</value>
<mod_level>M3001</mod_level>
<mod_name>$HBBLU$破壞神之毀滅$NOR$</mod_name>
<require>
level:30
str:60
</require>
<quality_level>4</quality_level>
<armor_prop>
armor:150
full_self:1
</armor_prop>
<enchase>
apply_prop/armor1:80
apply_prop/defense:30
apply_prop/dp_power:2
apply_prop/reduce_damage:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:80
apply_prop/defense:30
[/1]
[2]
id:magic stone
name:玄石
apply_prop/dp_power:2
apply_prop/reduce_damage:3
[/2]
</insert>
</A3016>
