from django.test import TestCase

from .models import Machine, Usine


class MachineModelTests(TestCase):
    def test_usine_creation(self):
        self.assertEqual(Machine.objects.count(), 0)
        Machine.objects.create(nom="four", prix=1_000)
        self.assertEqual(Machine.objects.count(), 2)


class UsineModelTests(TestCase):
    Usine.objects.first().costs()
