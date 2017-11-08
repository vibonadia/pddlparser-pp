(define (problem gripper_1_balls)
	(:domain gripper)

	(:objects
		rooma roomb - room
		ball1 - ball)

	(:init
		(free left)
		(free right)
		(at-robby rooma)
		(at-ball ball1 rooma)
	)

	(:goal
		(and
			(at-ball ball1 roomb)
		)
	)
)
