(define (domain gripper)
	(:requirements :strips :typing :non-deterministic)

	(:types room ball gripper)

	(:constants left right - gripper)

	(:predicates
		(at-robby ?r - room)
		(at-ball ?b - ball ?r - room)
		(free ?g - gripper)
		(carry ?o - ball ?g - gripper))

	(:action move
		:parameters  (?from ?to - room)
		:precondition (at-robby ?from)
		:effect (and  (at-robby ?to) (not (at-robby ?from))))

	(:action pick
		:parameters (?obj - ball ?room - room ?gripper - gripper)
		:precondition  (and  (at-ball ?obj ?room) (at-robby ?room) (free ?gripper))
		:nondeteffects
			:effect (and (not (carry ?obj ?gripper)))
			:effect (and (carry ?obj ?gripper) (not (at-ball ?obj ?room)) (not (free ?gripper)))
	)

	(:action drop
		:parameters (?obj - ball ?room - room ?gripper - gripper)
		:precondition (and (carry ?obj ?gripper) (at-robby ?room))
		:effect (and (at-ball ?obj ?room) (free ?gripper) (not (carry ?obj ?gripper))))
)
