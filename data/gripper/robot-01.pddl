(define (problem robot-01)
	(:domain gripper)

	(:objects
		rooma roomb - room
		ball1 - ball
		left - gripper)

	(:init
		(free left) 
		(at-robby rooma)
		(at-ball ball1 rooma) 
	)

	(:goal
		(and 
			(at-ball ball1 roomb)
		)
	)
)
