# BehaviorTree
My BehaviorTree lib

我的毕业设计：行为树

--------version0.1--------
--------2016/04/10--------

Control:sequence,selector,parallel,loop
Behavior:action

实现了顺序节点，选择节点，并行节点，循环节点，动作节点

样例中的结构如下：
				root
				|
				loop
				|
			selector
			|		|
		sequence	idle
		|		|
		move	attack
move的外部条件found(节点的 visable 为true)。
attck的外部条件是arrive(接近终点)，执行时将节点的 visable 设置为false。
idle执行时随机将节点设置x与y的值，结束时将节点的 visable 设置为true。