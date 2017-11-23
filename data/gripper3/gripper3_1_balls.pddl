(define (problem gripper3_1_balls)
	(:domain gripper)

	(:objects
		rooma roomb - room
		ball1 - ball)

	(:init
		(free left)
		(free right)
		(at-robby rooma)
		(at-ball ball1 rooma)
		(whole ball1)
	)

	(:goal
		(and
			(at-ball ball1 roomb)
		)
	)
)
