(define (problem robot-05)
	(:domain gripper)

	(:objects
		rooma roomb - room
		ball1 ball2 ball3 ball4 ball5 - ball
		left - gripper)

	(:init
		(free left) 
		(at-robby rooma)
		(at-ball ball1 rooma) 
		(at-ball ball2 rooma)
		(at-ball ball3 rooma)
		(at-ball ball4 rooma)
		(at-ball ball5 rooma)
	)

	(:goal
		(and 
			(at-ball ball1 roomb)
			(at-ball ball2 roomb)
			(at-ball ball3 roomb)
			(at-ball ball4 roomb)
			(at-ball ball5 roomb)
		)
	)
)
